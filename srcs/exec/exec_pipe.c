/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:56:37 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:51 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static void	exec_pipe_child(t_tree *node, t_general_info *info,
		int *pipe_arr, int child_nb)
{
	int	ret;

	if (child_nb && dup2(pipe_arr[child_nb * 2 - 2], STDIN_FILENO) < 0)
	{
		perror(info->prog_name);
		close_pipes(pipe_arr, -1);
		free(pipe_arr);
		exit_command_node(info, 1, -1);
	}
	if (pipe_arr[child_nb * 2] >= 0
		&& dup2(pipe_arr[child_nb * 2 + 1], STDOUT_FILENO) < 0)
	{
		perror(info->prog_name);
		close_pipes(pipe_arr, -1);
		free(pipe_arr);
		exit_command_node(info, 1, -1);
	}
	close_pipes(pipe_arr, -1);
	free(pipe_arr);
	ret = exec_node(node, info, 1);
	if (ret)
		exit_command_node(info, 1, ret);
	exit_command_node(info, 1, info->exit_code);
}

static int	*fork_pipe_children(t_tree *node, t_general_info *info,
			int *pipe_arr, int nb_children)
{
	int	i;
	int	*pid_arr;

	pid_arr = malloc(sizeof(int) * nb_children);
	if (!pid_arr)
	{
		perror(info->prog_name);
		return (NULL);
	}
	i = -1;
	while (++i < nb_children)
	{
		pid_arr[i] = fork();
		if (pid_arr[i] < 0)
		{
			perror(info->prog_name);
			return (NULL);
		}
		if (pid_arr[i] == 0)
		{
			free(pid_arr);
			exec_pipe_child(node->pipe_children[i], info, pipe_arr, i);
		}
	}
	return (pid_arr);
}

static void	wait_pipe_children(int *pid_arr, int nb_children,
				t_general_info *info)
{
	int	i;

	i = 0;
	while (i < nb_children)
	{
		if (i == nb_children - 1)
			wait_child(pid_arr[i], info);
		else
			waitpid(pid_arr[i], NULL, 0);
		i++;
	}
	free(pid_arr);
}

int	exec_pipe(t_tree *node, t_general_info *info)
{
	int	nb_com;
	int	*pipe_fd;
	int	*pid_arr;

	nb_com = 0;
	while (node->pipe_children[nb_com])
		nb_com++;
	pipe_fd = open_pipes(nb_com - 1, info->prog_name);
	if (!pipe_fd)
		return (-1);
	pid_arr = fork_pipe_children(node, info, pipe_fd, nb_com);
	close_pipes(pipe_fd, -1);
	free(pipe_fd);
	if (!pid_arr)
	{
		while (wait(NULL) >= 0)
			;
		free(pid_arr);
		return (-1);
	}
	wait_pipe_children(pid_arr, nb_com, info);
	return (0);
}
