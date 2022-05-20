/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:30:46 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 15:36:59 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	disable_stdout(char *prog_name)
{
	int	fd;
	int	fd_save;

	fd_save = dup(STDOUT_FILENO);
	if (fd_save < 0)
	{
		perror(prog_name);
		return (fd_save);
	}
	fd = open("/dev/null", O_RDONLY);
	if (fd_save < 0)
	{
		perror(prog_name);
		close(fd_save);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror(prog_name);
		close(fd);
		close(fd_save);
		return (-1);
	}
	close(fd);
	return (fd_save);
}

int	restore_stdout(int fd_save, char *prog_name)
{
	if (dup2(fd_save, STDOUT_FILENO) < 0)
	{
		perror(prog_name);
		return (-1);
	}
	close(fd_save);
	return (0);
}

char	*get_input(char *prog_name)
{
	char	*prompt;
	char	*input;
	int		fd_save;

	if (isatty(STDIN_FILENO))
		prompt = "$ ";
	else
	{
		prompt = NULL;
		fd_save = disable_stdout(prog_name);
		if (fd_save < 0)
			return (NULL);
	}
	input = readline(prompt);
	if (!isatty(STDIN_FILENO) && restore_stdout(fd_save, prog_name))
	{
		free(input);
		return (NULL);
	}
	return (input);
}
