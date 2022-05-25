/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:59:46 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/25 12:00:47 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_search.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

static int	file_error(char *prog_name, char *filename, int exist)
{
	char	*to_print;
	char	*error_str;
	int		len;

	error_str = strerror(errno);
	len = ft_strlen(filename) + ft_strlen(prog_name) + ft_strlen(error_str) + 6;
	to_print = ft_calloc(len, sizeof(char));
	if (to_print == NULL)
		return (free_perror_and_ret(NULL, prog_name, 1, -1));
	ft_strlcat(to_print, prog_name, len);
	ft_strlcat(to_print, ": ", len);
	ft_strlcat(to_print, filename, len);
	ft_strlcat(to_print, ": ", len);
	ft_strlcat(to_print, error_str, len);
	ft_strlcat(to_print, "\n", len);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	if (exist)
		return (126);
	return (127);
}

int	check_file(char *filename, char *prog_name, int path_search)
{
	struct stat	buf;

	if (path_search && access(filename, F_OK))
		return (1);
	if (!path_search && access(filename, F_OK))
		return (file_error(prog_name, filename, 0));
	if (access(filename, X_OK))
		return (file_error(prog_name, filename, 1));
	if (stat(filename, &buf))
		return (free_perror_and_ret(NULL, prog_name, 1, 1));
	if (!path_search && S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(prog_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (126);
	}
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}
