/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:01:35 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/03 15:51:47 by marnaudy         ###   ########.fr       */
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

static int	get_token_len(char *input, int idx, int *token_len)
{
	int	ret;

	while (1)
	{
		ret = skip_quote(input, idx, token_len);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			continue ;
		ret = skip_parameter(input, idx, token_len);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			continue ;
		if (!can_add_to_token(&input[idx], *token_len))
			return (0);
		(*token_len)++;
	}
}

static int	get_next_token(char *input, int *idx, char **token)
{
	int	token_len;
	int	ret;

	*token = NULL;
	while (is_blank(input[*idx]))
		(*idx)++;
	if (input[*idx] == 0)
		return (0);
	token_len = 0;
	ret = get_token_len(input, *idx, &token_len);
	if (ret < 0)
		return (1);
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
