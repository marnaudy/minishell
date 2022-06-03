/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:24:46 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/03 10:38:56 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

void	close_pipes(int	*pipe_fd, int nb_to_close)
{
	int	i;

	i = 0;
	while (i < nb_to_close || (nb_to_close < 0 && pipe_fd[i] >= 0))
	{
		close(pipe_fd[i]);
		i++;
	}
}

int	*open_pipes(int nb_pipes, char *prog_name)
{
	int	*pipe_fd;
	int	i;

	pipe_fd = malloc(sizeof(int) * (nb_pipes * 2 + 1));
	if (!pipe_fd)
	{
		perror(prog_name);
		return (NULL);
	}
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&pipe_fd[2 * i]))
		{
			perror(prog_name);
			close_pipes(pipe_fd, i);
			return (NULL);
		}
		i++;
	}
	pipe_fd[2 * i] = -1;
	return (pipe_fd);
}
