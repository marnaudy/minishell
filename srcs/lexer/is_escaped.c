/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_escaped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:17:59 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 15:45:31 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_escaped_in_braces(char *str, int pos, int *idx);

static int	is_escaped_in_singles(char *str, int pos, int *idx)
{
	while (*idx < pos)
	{
		if (str[*idx] == '\'')
			return (-1);
		(*idx)++;
	}
	return (!(str[*idx] == '\''));
}

static int	is_escaped_in_doubles(char *str, int pos, int *idx)
{
	int	ret;

	while (*idx < pos)
	{
		if (str[*idx] == '\"')
			return (-1);
		if (str[*idx] == '$' && str[*idx + 1] == '{')
		{
			(*idx)++;
			ret = is_escaped_in_braces(str, pos, idx);
			if (ret >= 0)
				return (ret);
		}
		if (str[*idx] == '\\')
		{
			if (*idx + 1 == pos)
				return (1);
			(*idx)++;
		}
		(*idx)++;
	}
	return (!(ft_is_in_charset(str[*idx], "$\"") || (str[*idx] == '\\'
				&& ft_is_in_charset(str[*idx + 1], "$\"\\"))));
}

static int	is_escaped_in_quotes(char *str, int pos, int *idx)
{
	(*idx)++;
	if (str[*idx - 1] == '\"')
		return (is_escaped_in_doubles(str, pos, idx));
	return (is_escaped_in_singles(str, pos, idx));
}

static int	is_escaped_in_braces(char *str, int pos, int *idx)
{
	int	ret;

	while (*idx < pos)
	{
		if (str[*idx] == '}')
			return (-1);
		if (str[*idx] == '\"' || str[*idx] == '\'')
		{
			ret = is_escaped_in_quotes(str, pos, idx);
			if (ret >= 0)
				return (ret);
		}
		if (str[*idx] == '\\')
		{
			if (*idx + 1 == pos)
				return (1);
			(*idx)++;
		}
		(*idx)++;
	}
	return (!(ft_is_in_charset(str[*idx], "\'\"}") || (str[*idx] == '\\'
				&& ft_is_in_charset(str[*idx + 1], "\'\"\\}"))));
}

int	is_escaped(char *str, int pos)
{
	int	idx;
	int	ret;

	idx = 0;
	while (idx < pos)
	{
		ret = -1;
		if (str[idx] == '\"' || str[idx] == '\'')
			ret = is_escaped_in_quotes(str, pos, &idx);
		if (ret < 0 && str[idx] == '$' && str[idx + 1] == '{')
		{
			idx++;
			ret = is_escaped_in_braces(str, pos, &idx);
		}
		if (ret >= 0)
			return (ret);
		if (str[idx] == '\\')
		{
			if (idx + 1 == pos)
				return (1);
			idx++;
		}
		idx++;
	}
	return (0);
}
