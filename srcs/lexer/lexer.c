/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:01:35 by marnaudy          #+#    #+#             */
/*   Updated: 2022/04/29 17:04:54 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	add_token(char *token, t_list **list)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (!new)
	{
		free(token);
		return (-1);
	}
	ft_lstadd_back(list, new);
	return (0);
}

static int	quote_len(char *str)
{
	int		len;
	char	quote_char;

	quote_char = str[0];
	len = 1;
	while (str[len] && str[len] != quote_char)
		len++;
	if (str[len] == quote_char)
		return (len + 1);
	return (-1);
}

static int	skip_quote(char *input, int idx, int *token_len)
{
	int	len_quote;

	if (input[idx + *token_len] == '\"' || input[idx + *token_len] == '\"')
	{
		len_quote = quote_len(&input[idx + *token_len]);
		if (len_quote < 0)
		{
			write(STDERR_FILENO, "Unclosed quote\n", 15);
			return (1);
		}
		*token_len += len_quote;
	}
	return (0);
}

static int	get_next_token(char *input, int *idx, char **token)
{
	int	token_len;

	*token = NULL;
	while (is_blank(input[*idx]))
		(*idx)++;
	if (input[*idx] == 0)
		return (0);
	token_len = 1;
	while (1)
	{
		if (skip_quote(input, *idx, &token_len))
			return (1);
		if (!can_add_to_token(&input[*idx], token_len))
			break ;
		token_len++;
	}
	*token = ft_substr(input, *idx, token_len);
	if (!token)
		return (-1);
	*idx += token_len;
	return (0);
}

int	lexer(t_list **list, char *input, char *prog_name)
{
	int		idx;
	char	*token;
	int		error;

	*list = NULL;
	idx = 0;
	while (1)
	{
		error = get_next_token(input, &idx, &token);
		if (error != 0)
		{
			if (error == -1)
				perror(prog_name);
			ft_lstclear(list, &free);
			return (error);
		}
		if (token == NULL)
			return (0);
		if (add_token(token, list) != 0)
		{
			perror(prog_name);
			ft_lstclear(list, &free);
			return (-1);
		}
	}
}
