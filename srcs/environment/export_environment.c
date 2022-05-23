/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:49:06 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 12:46:33 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	env_list_size(t_env_list *list)
{
	int	nb;

	nb = 0;
	while (list)
	{
		if (list->export)
			nb++;
		list = list->next;
	}
	return (nb);
}

static char	*export_key_val_pair(t_env_list *pair, char *prog_name)
{
	char	*str;

	str = malloc(sizeof(char)
			* (ft_strlen(pair->key) + ft_strlen(pair->value) + 2));
	if (!str)
	{
		perror(prog_name);
		return (NULL);
	}
	ft_strlcpy(str, pair->key, ft_strlen(pair->key) + 1);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, pair->value, ft_strlen(str) + ft_strlen(pair->value) + 2);
	return (str);
}

int	free_char_array_and_ret(char **arr, int ret)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (ret);
}

int	export_env(t_general_info *info, char ***env_arr)
{
	t_env_list	*list;
	int			i;

	*env_arr = ft_calloc(env_list_size(info->env) + 1, sizeof(char *));
	if (!*env_arr)
	{
		perror(info->prog_name);
		return (-1);
	}
	list = info->env;
	i = 0;
	while (list)
	{
		if (list->export)
		{
			(*env_arr)[i] = export_key_val_pair(list, info->prog_name);
			if (!(*env_arr)[i])
				return (free_char_array_and_ret(*env_arr, -1));
			i++;
		}
		list = list->next;
	}
	(*env_arr)[i] = NULL;
	return (0);
}
