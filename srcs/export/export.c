/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:52:14 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 15:39:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	export_equal(char *key, char *value, t_general_info *info)
{
	char	*old_value;

	if (!value)
	{
		old_value = fetch_value(info->env, key);
		if (old_value)
			value = ft_strdup(old_value);
		else
			value = NULL;
		if (old_value && !value)
		{
			perror(info->prog_name);
			return (-1);
		}
		if (add_to_env(info, key, value, 2))
			return (-1);
		return (0);
	}
	if (add_to_env(info, key, value, 1))
		return (-1);
	return (0);
}

int	export_plus_equal(char *key, char *value, t_general_info *info)
{
	char	*old_value;
	char	*new_value;

	old_value = fetch_value(info->env, key);
	if (old_value)
	{
		new_value = ft_strjoin(old_value, value);
		if (!new_value)
		{
			perror(info->prog_name);
			free(value);
			return (-1);
		}
		free(value);
	}
	else
		new_value = value;
	if (add_to_env(info, key, new_value, 1))
		return (-1);
	return (0);
}

int	get_key_and_val(char *arg, t_general_info *info, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] != '=' && (arg[i] != '+' || arg[i + 1] != '=')))
		i++;
	*key = ft_substr(arg, 0, i);
	if (!*key)
		return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
	if (!is_valid_parameter(*key, -1))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(*key, STDERR_FILENO);
		ft_putstr_fd(&arg[i], STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (free_and_ret(*key, NULL, 1));
	}
	if (arg[i] == '=')
		*value = ft_strdup(arg + i + 1);
	else if (arg[i] == '+' && arg[i + 1] == '=')
		*value = ft_strdup(arg + i + 2);
	else
		*value = NULL;
	if (!*value && (arg[i] == '=' || (arg[i] == '+' && arg[i + 1] == '=')))
		return (free_perror_and_ret(*key, info->prog_name, 1, -1));
	return (0);
}

int	export_arg(char *arg, t_general_info *info)
{
	char	*key;
	char	*value;
	int		ret;
	int		i;

	i = 0;
	while (arg[i] && (arg[i] != '=' && (arg[i] != '+' || arg[i + 1] != '=')))
		i++;
	ret = get_key_and_val(arg, info, &key, &value);
	if (ret)
		return (ret);
	if (arg[i] == '+')
	{
		if (export_plus_equal(key, value, info))
			return (-1);
	}
	else
	{
		if (export_equal(key, value, info))
			return (-1);
	}
	return (0);
}

int	export(t_tree *node, int fd_out, t_general_info *info)
{
	t_list	*tmp;
	int		ret;
	int		exit_code;

	if (!node->arg->next)
		return (display_export_env(info, fd_out));
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	exit_code = 0;
	tmp = node->arg->next;
	while (tmp)
	{
		ret = export_arg(tmp->content, info);
		if (ret < 0)
			return (-1);
		if (ret)
			exit_code = 1;
		tmp = tmp->next;
	}
	return (exit_code);
}
