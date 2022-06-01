/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:34:50 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 17:10:09 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

static int	parameter_len_no_brace(char *str, int start, int ignore_quotes)
{
	int	len;

	if (str[start] != '$' || (is_escaped(str, start) && !ignore_quotes))
		return (0);
	if (str[start + 1] == '?')
		return (2);
	str[start] = 'a';
	if (!is_escaped(str, start)
		&& (str[start + 1] == '\"' || str[start + 1] == '\''))
	{
		str[start] = '$';
		return (1);
	}
	str[start] = '$';
	if (!is_valid_parameter(&str[start + 1], 1))
		return (0);
	len = 2;
	while (str[start + len] && is_valid_parameter(&str[start + 1], len))
		len++;
	return (len);
}

static int	parameter_len_brace(char *str, int start, int ignore_quotes)
{
	int	len;
	int	ret;

	if (str[start] != '$' || str[start + 1] != '{'
		|| (is_escaped(str, start) && !ignore_quotes))
		return (0);
	len = 1;
	while (1)
	{
		ret = 0;
		while (ret == 0)
			ret = skip_quote(str, start, &len);
		if (str[start + len] == '\0')
			return (-1);
		if (str[start + len] == '}'
			&& (!is_escaped(str, start + len) || ignore_quotes))
			return (len + 1);
		len++;
	}
}

int	parameter_len(char *str, int start, int ignore_quotes)
{
	int	ret;

	ret = parameter_len_no_brace(str, start, ignore_quotes);
	if (ret)
		return (ret);
	return (parameter_len_brace(str, start, ignore_quotes));
}
