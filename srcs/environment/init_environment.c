/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:26:38 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/05 15:31:05 by marnaudy         ###   ########.fr       */
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

static int	parse_env(char *env, t_hash_table *table)
{
	char	*key;
	char	*value;
	int		ret;

	ret = split_equal(&key, &value, env);
	if (ret)
		return (ret);
	if (add_to_table(table, key, value))
	{
		free(key);
		free(value);
		return (-1);
	}
	return (0);
}

t_hash_table	*init_env_table(char **envp)
{
	t_hash_table	*new_table;
	int				i;

	new_table = ft_calloc(sizeof(t_hash_table), 1);
	if (!new_table)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (parse_env(envp[i], new_table) < 0)
		{
			free_hash_table(new_table);
			return (NULL);
		}
		i++;
	}
	return (new_table);
}