/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:26:38 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 16:04:19 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	is_valid_parameter(char *parameter, int len)
{
	int	i;

	if (len < 0)
		len = ft_strlen(parameter);
	if (parameter == NULL)
		return (0);
	if (!(ft_isalpha(parameter[0]) || parameter[0] == '_'))
		return (0);
	i = 1;
	while (parameter[i] && i < len)
	{
		if (!(ft_isalnum(parameter[i]) || parameter[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	split_equal(char **key, char **value, char *input)
{
	int		i;

	i = 0;
	*value = NULL;
	while (input[i] && input[i] != '=')
		i++;
	if (input[i] == 0)
		return (1);
	*key = ft_substr(input, 0, i);
	if (!*key)
		return (-1);
	if (!is_valid_parameter(*key, -1))
	{
		free(*key);
		return (1);
	}
	*value = ft_substr(input, i + 1, ft_strlen(&input[i + 1]));
	if (!*value)
	{
		free(*key);
		return (-1);
	}
	return (0);
}

static int	parse_env(char *env, t_general_info *info)
{
	char	*key;
	char	*value;
	int		ret;

	ret = split_equal(&key, &value, env);
	if (ret == -1)
		perror(info->prog_name);
	if (ret)
		return (ret);
	if (add_to_env(info, key, value, 1))
	{
		free(key);
		free(value);
		return (-1);
	}
	return (0);
}

static int	add_path(t_general_info *info)
{
	char	*key;
	char	*path;

	path = fetch_value(info->env, "PATH");
	if (path)
		return (0);
	path = ft_strdup(
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	if (!path)
	{
		perror(info->prog_name);
		return (-1);
	}
	key = ft_strdup("PATH");
	if (!key)
	{
		perror(info->prog_name);
		free(path);
		return (-1);
	}
	return (add_to_env(info, key, path, 0));
}

int	init_env_list(char **envp, t_general_info *info)
{
	int			i;

	info->env = NULL;
	i = 0;
	while (envp[i])
	{
		if (parse_env(envp[i], info) < 0)
		{
			free_env_list(&info->env);
			return (-1);
		}
		i++;
	}
	remove_value(&info->env, "_");
	return (add_path(info));
}
