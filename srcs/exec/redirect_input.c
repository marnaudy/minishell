/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:37:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/19 16:02:58 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static int	write_here_doc(char *here_doc, t_general_info *info, int pipe_fd[2])
{
	free(info->prog_name);
	free_hash_table(info->table);
	free(info);
	close(pipe_fd[0]);
	write(pipe_fd[1], here_doc, ft_strlen(here_doc));
	close(pipe_fd[1]);
	free_tree(&info->root);
	exit(0);
}

static int	launch_here_doc_writer(char *here_doc, t_general_info *info)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd))
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		write_here_doc(here_doc, info, pipe_fd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	redirect_input(t_tree *node, int is_child, t_general_info *info)
{
	int	fd;

	fd = STDIN_FILENO;
	if (node->infile)
		fd = open(node->infile, O_RDONLY);
	if (node->here_doc)
		fd = launch_here_doc_writer(node->here_doc->content, info);
	if (fd < 0)
		return (print_file_error(info->prog_name, node->infile));
	if (is_child && (node->infile || node->here_doc))
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror(info->prog_name);
			close(fd);
			return (-2);
		}
		close(fd);
		return (STDIN_FILENO);
	}
	return (fd);
}
