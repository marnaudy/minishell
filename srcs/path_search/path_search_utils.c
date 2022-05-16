/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:06:33 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/16 17:10:02 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_search.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

static int	free_perror_ret(char *to_free, char *prog_name)
{
	perror(prog_name);
	free(to_free);
	return (-1);
}

static int	not_executable_error(char *prog_name, char *path)
{
	char	*to_print;
	char	*to_free;

	to_print = ft_strcat(": ", strerror(errno));
	if (!to_print)
		return (free_perror_ret(NULL, prog_name));
	to_free = to_print;
	to_print = ft_strcat(path, to_print);
	if (!to_print)
		return (free_perror_ret(to_free, prog_name));
	free(to_free);
	to_free = to_print;
	to_print = ft_strcat(": ", to_print);
	if (!to_print)
		return (free_perror_ret(to_free, prog_name));
	free(to_free);
	to_free = to_print;
	to_print = ft_strcat(prog_name, to_print);
	if (!to_print)
		return (free_perror_ret(to_free, prog_name));
	free(to_free);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	write(STDERR_FILENO, "\n", 1);
	free(to_print);
	return (1);
}

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
	if (access(*path, X_OK))
		return (not_executable_error(prog_name, *path));
	return (0);
}

int	search_path_array(char *arg0, char **path,
				char **path_arr, char *prog_name)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		if (path_arr[i][0])
			full_path = ft_strcat_with_slash(path_arr[i], arg0);
		else
			full_path = ft_strcat(path_arr[i], arg0);
		if (!full_path)
		{
			perror(prog_name);
			return (-1);
		}
		if (!access(full_path, X_OK))
		{
			*path = full_path;
			return (0);
		}
		free(full_path);
		i++;
	}
	return (not_executable_error(prog_name, arg0));
}
