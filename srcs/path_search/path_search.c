/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:09:20 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 12:40:27 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_search.h"

static void	free_char_array(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

int	search_path(char *arg0, char **path, t_env_list *env_list, char *prog_name)
{
	char	*path_value;
	char	**path_arr;
	int		ret;

	*path = arg0;
	if (ft_is_in_charset('/', arg0))
		return (no_path_search(arg0, path, prog_name));
	path_value = fetch_value(env_list, "PATH");
	if (!path_value)
		return (no_path_search(arg0, path, prog_name));
	path_arr = split_path(path_value, prog_name);
	if (!path_arr)
		return (-1);
	ret = search_path_array(arg0, path, path_arr, prog_name);
	free_char_array(path_arr);
	return (ret);
}
