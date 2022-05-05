/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:34:50 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/05 18:35:23 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

static int	parameter_len_no_brace(char *str)
{
	int	len;

	if (str[0] != '$')
		return (0);
	if (str[1] == '?')
		return (2);
	if (!is_valid_parameter(&str[1], 1))
		return (0);
	len = 2;
	while (str[len] && is_valid_parameter(&str[1], len))
		len++;
	return (len);
}

static int	parameter_len_brace(char *str)
{
	int	len;
	int	ret;

	if (str[0] != '$' || str[1] != '{')
		return (0);
	len = 1;
	while (1)
	{
		ret = 0;
		while (ret == 0)
			ret = skip_quote(str, 0, &len);
		if (str[len] == '}')
			return (len + 1);
		len++;
	}
}

int	parameter_len(char *str)
{
	int	ret;

	ret = parameter_len_no_brace(str);
	if (ret)
		return (ret);
	return (parameter_len_brace(str));
}
