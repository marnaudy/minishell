/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_parameter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:48:00 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/06 11:35:30 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parameter_expansion.h"

static int	free_and_ret(char *s1, int ret)
{
	free(s1);
	return (ret);
}

static int	replace_parameter_exit_code(char **str, int exit_code,
		int *idx, int param_len)
{
	char	*value;
	char	*new_str;

	value = ft_itoa(exit_code);
	if (!value)
		return (-1);
	new_str = replace_in_str(*str, *idx, param_len, value);
	if (!new_str)
		return (free_and_ret(value, -1));
	(*idx) += ft_strlen(value) - 1;
	free(value);
	free(*str);
	*str = new_str;
	return (0);
}

static int	replace_parameter_no_brace(char **str, int *idx,
		t_hash_table *table, int param_len)
{
	char	*new_str;
	char	*parameter;
	char	*value;

	parameter = ft_substr(*str, (*idx) + 1, param_len - 1);
	if (!parameter)
		return (-1);
	value = fetch_value(table, parameter);
	new_str = replace_in_str(*str, *idx, param_len, value);
	if (!new_str)
		return (free_and_ret(parameter, -1));
	(*idx) += ft_strlen(value) - 1;
	free(*str);
	*str = new_str;
	return (free_and_ret(parameter, 0));
}

static int	replace_parameter_brace(char **str, int *idx,
		t_hash_table *table, char *prog_name)
{
	char	*new_str;
	char	*parameter;
	char	*value;
	int		param_len;

	param_len = parameter_len(&(*str)[*idx]);
	if (param_len == -1)
		return (bad_sub_message(&(*str)[*idx], prog_name, 0));
	parameter = ft_substr(&(*str)[2], *idx, param_len - 3);
	if (!parameter)
		return (-1);
	if (!is_valid_parameter(parameter, -1))
		return (free_and_ret(parameter,
				bad_sub_message(parameter, prog_name, 1)));
	value = fetch_value(table, parameter);
	new_str = replace_in_str(*str, *idx, param_len, value);
	if (!new_str)
		return (free_and_ret(parameter, -1));
	(*idx) += ft_strlen(value) - 1;
	free(*str);
	*str = new_str;
	return (free_and_ret(parameter, 0));
}

int	replace_parameter(char **str, int *idx, t_general_info *info)
{
	int	param_len;

	param_len = parameter_len(&(*str)[*idx]);
	if (!param_len)
		return (0);
	if (!ft_strncmp(&(*str)[*idx], "$?", 2)
		|| !ft_strncmp(&(*str)[*idx], "${?}", 4))
		return (
			replace_parameter_exit_code(str, info->exit_code, idx, param_len));
	if ((*str)[(*idx) + 1] != '{')
		return (replace_parameter_no_brace(str, idx, info->table, param_len));
	return (replace_parameter_brace(str, idx, info->table, info->prog_name));
}
