/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:37:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 15:52:55 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static int	write_here_doc(char *here_doc, t_general_info *info, int pipe_fd[2])
{
	free(info->prog_name);
	free_env_list(&info->env);
	close(pipe_fd[0]);
	write(pipe_fd[1], here_doc, ft_strlen(here_doc));
	close(pipe_fd[1]);
	free_tree(&info->root);
	free(info);
	exit(0);
}

static int	launch_here_doc_writer(char *here_doc, t_general_info *info)
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

int	open_infile(t_tree *node, char *prog_name)
{
	int		fd;
	t_list	*to_free;

	fd = STDIN_FILENO;
	while (node->infile)
	{
		fd = open((char *)node->infile->content, O_RDONLY, 00644);
		if (fd < 0)
			return (print_file_error(prog_name, node->infile->content));
		to_free = node->infile;
		node->infile = node->infile->next;
		free(to_free->content);
		free(to_free);
		if (node->infile)
			close(fd);
	}
	return (fd);
}

int	redirect_input(t_tree *node, int is_child, t_general_info *info)
{
	int	fd;

	fd = open_infile(node, info->prog_name);
	if (fd < 0)
		return (-1);
	if (node->here_doc)
	{
		if (fd != STDOUT_FILENO)
			close(fd);
		fd = launch_here_doc_writer(node->here_doc->content, info);
		if (fd < 0)
			return (-1);
	}
	if (is_child && fd != STDIN_FILENO)
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
