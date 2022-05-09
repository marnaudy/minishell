/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:39:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 11:53:29 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	skip_parameter(char *input, int idx, int *tk_l)
{
	int	ret;

	if (input[idx + *tk_l] != '$' || input[idx + *tk_l + 1] != '{'
		|| is_escaped(input, idx + *tk_l))
		return (1);
	(*tk_l) += 2;
	while (1)
	{
		ret = 0;
		while (ret == 0)
			ret = skip_quote(input, idx, tk_l);
		if (ret == -1)
			return (-1);
		if (input[idx + *tk_l] == 0)
		{
			write(STDERR_FILENO, "Unclosed parameter\n", 19);
			return (-1);
		}
		if (input[idx + *tk_l] == '}' && !is_escaped(input, idx + *tk_l))
		{
			(*tk_l)++;
			return (0);
		}
		(*tk_l)++;
	}
}
