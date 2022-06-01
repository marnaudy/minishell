/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_parameter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:48:00 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 16:52:02 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parameter_expansion.h"

int	free_and_ret(char *s1, char *s2, int ret)
{
	free(s1);
	free(s2);
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
		return (free_and_ret(value, NULL, -1));
	(*idx) += ft_strlen(value) - 1;
	free(value);
	free(*str);
	*str = new_str;
	return (0);
}

static int	replace_parameter_no_brace(char **str, int *idx,
		t_env_list *env_list, int param_len)
{
	char	*new_str;
	char	*parameter;
	char	*value;

	parameter = ft_substr(*str, (*idx) + 1, param_len - 1);
	if (!parameter)
		return (-1);
	value = fetch_value(env_list, parameter);
	new_str = replace_in_str(*str, *idx, param_len, value);
	if (!new_str)
		return (free_and_ret(parameter, NULL, -1));
	(*idx) += ft_strlen(value) - 1;
	free(*str);
	*str = new_str;
	return (free_and_ret(parameter, NULL, add_backslash(str,
				*idx + 1 - ft_strlen(value), ft_strlen(value))));
}

static int	replace_parameter_brace(char **str, int *idx,
		int param_len, t_general_info *info)
{
	char	*new_str;
	char	*parameter;
	char	*value;

	if (param_len == -1)
		return (bad_sub_message(*str, info->prog_name, 0));
	parameter = ft_substr(&(*str)[2], *idx, param_len - 3);
	if (!parameter)
		return (-1);
	if (!is_valid_parameter(parameter, -1))
		return (free_and_ret(parameter, NULL,
				bad_sub_message(*str, info->prog_name, 0)));
	value = fetch_value(info->env, parameter);
	new_str = replace_in_str(*str, *idx, param_len, value);
	if (!new_str)
		return (free_and_ret(parameter, NULL, -1));
	(*idx) += ft_strlen(value) - 1;
	free(*str);
	*str = new_str;
	return (free_and_ret(parameter, NULL, add_backslash(str,
				*idx + 1 - ft_strlen(value), ft_strlen(value))));
}

int	replace_parameter(char **str, int *idx,
		t_general_info *info, int ignore_quotes)
{
	int	param_len;

	param_len = parameter_len(*str, *idx, ignore_quotes);
	if (!param_len)
		return (0);
	if ((!ft_strncmp(&(*str)[*idx], "$?", 2)
		|| !ft_strncmp(&(*str)[*idx], "${?}", 4))
		&& (!is_escaped(*str, *idx) || ignore_quotes))
		return (
			replace_parameter_exit_code(str, info->exit_code, idx, param_len));
	if ((*str)[(*idx) + 1] != '{')
		return (replace_parameter_no_brace(str, idx, info->env, param_len));
	return (replace_parameter_brace(str, idx, param_len, info));
}
