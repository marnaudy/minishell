/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:39:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/03 16:12:39 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	skip_parameter(char *input, int idx, int *token_len)
{
	int	ret;

	if (input[idx + *token_len] != '$' || input[idx + *token_len + 1] != '{')
		return (1);
	(*token_len) += 2;
	while (1)
	{
		ret = 0;
		while (ret == 0)
			ret = skip_quote(input, idx, token_len);
		if (ret == -1)
			return (-1);
		if (input[idx + *token_len] == 0)
		{
			write(STDERR_FILENO, "Unclosed parameter\n", 19);
			return (-1);
		}
		if (input[idx + *token_len] == '}')
		{
			(*token_len)++;
			return (0);
		}
		(*token_len)++;
	}
}
