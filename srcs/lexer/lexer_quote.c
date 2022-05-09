/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:38:39 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 12:23:52 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	skip_simple_quote(char *input, int idx, int *token_len)
{
	if (input[idx + *token_len] != '\'' || is_escaped(input, idx + *token_len))
		return (1);
	(*token_len)++;
	while (1)
	{
		if (input[idx + *token_len] == 0)
		{
			write(STDERR_FILENO, "Unclosed quote\n", 15);
			return (-1);
		}
		if (input[idx + *token_len] == '\''
			&& !is_escaped(input, idx + *token_len))
		{
			(*token_len)++;
			return (0);
		}
		(*token_len)++;
	}
}

static int	skip_double_quote(char *input, int idx, int *token_len)
{
	int	ret;

	(*token_len)++;
	while (1)
	{
		ret = 0;
		while (ret == 0)
			ret = skip_parameter(input, idx, token_len);
		if (ret == -1)
			return (-1);
		if (input[idx + *token_len] == 0)
		{
			write(STDERR_FILENO, "Unclosed quote\n", 15);
			return (-1);
		}
		if (input[idx + *token_len] == '\"'
			&& !is_escaped(input, idx + *token_len))
		{
			(*token_len)++;
			return (0);
		}
		(*token_len)++;
	}
}

int	skip_quote(char *input, int idx, int *token_len)
{
	if (is_escaped(input, idx + *token_len))
		return (1);
	if (input[idx + *token_len] == '\"')
		return (skip_double_quote(input, idx, token_len));
	if (input[idx + *token_len] == '\'')
		return (skip_simple_quote(input, idx, token_len));
	return (1);
}
