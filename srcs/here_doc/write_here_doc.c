/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:09:52 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/27 15:37:21 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static int	write_here_doc(char *here_doc, t_general_info *info, int pipe_fd[2])
{
	close(pipe_fd[0]);
	rl_clear_history();
	write(pipe_fd[1], here_doc, ft_strlen(here_doc));
	close(pipe_fd[1]);
	free_general_info(info);
	exit(0);
}

int	launch_here_doc_writer(char *here_doc, t_general_info *info)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd))
	{
		perror(info->prog_name);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror(info->prog_name);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		write_here_doc(here_doc, info, pipe_fd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
