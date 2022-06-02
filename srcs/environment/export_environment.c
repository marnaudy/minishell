/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:49:06 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 15:39:33 by marnaudy         ###   ########.fr       */
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

int	add_underscore(char **env_arr, int idx, char *underscore, char *prog_name)
{
	t_env_list	new;

	new.export = 1;
	new.key = "_";
	new.value = underscore;
	new.next = NULL;
	env_arr[idx] = export_key_val_pair(&new, prog_name);
	if (!env_arr[idx])
		return (-1);
	return (0);
}

int	export_env(t_general_info *info, char ***env_arr, char *underscore)
{
	t_env_list	*list;
	int			i;

	*env_arr = ft_calloc(env_list_size(info->env) + 2, sizeof(char *));
	if (!*env_arr)
		free_perror_and_ret(NULL, info->prog_name, 1, -1);
	list = info->env;
	i = 0;
	while (list)
	{
		if (list->export == 1)
		{
			(*env_arr)[i] = export_key_val_pair(list, info->prog_name);
			if (!(*env_arr)[i])
				return (free_char_array_and_ret(*env_arr, -1));
			i++;
		}
		list = list->next;
	}
	if (add_underscore(*env_arr, i, underscore, info->prog_name))
		return (free_char_array_and_ret(*env_arr, -1));
	(*env_arr)[i + 1] = NULL;
	return (0);
}
