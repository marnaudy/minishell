/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:06:33 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 15:06:35 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_search.h"

char	*ft_strcat_with_slash(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = '/';
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = 0;
	return (new);
}

int	no_path_search(char *arg0, char **path, char *prog_name)
{
	*path = arg0;
	return (check_file(arg0, prog_name, 0));
}

int	command_not_found(char *prog_name, char *arg0)
{
	char	*to_print;

	to_print = ft_strcat(arg0, ": command not found\n");
	if (!to_print)
	{
		perror(prog_name);
		return (-1);
	}
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	return (127);
}

int	search_path_array(char *arg0, char **path,
				char **path_arr, char *prog_name)
{
	char	*full_path;
	int		i;
	int		ret;

	i = 0;
	while (path_arr[i])
	{
		if (path_arr[i][0])
			full_path = ft_strcat_with_slash(path_arr[i], arg0);
		else
			full_path = ft_strcat(path_arr[i], arg0);
		if (!full_path)
			return (free_perror_and_ret(NULL, prog_name, 1, -1));
		ret = check_file(full_path, prog_name, 1);
		if (ret == 0)
			*path = full_path;
		else
			free(full_path);
		if (ret != 1)
			return (ret);
		i++;
	}
	return (command_not_found(prog_name, arg0));
}
