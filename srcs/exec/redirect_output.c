/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:37:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 16:00:54 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	open_outfile(t_tree *node, char *prog_name)
{
	int			fd;
	t_file_list	*to_free;

	fd = STDOUT_FILENO;
	while (node->outfile)
	{
		if (node->outfile->append)
			fd = open(node->outfile->name,
					O_WRONLY | O_APPEND | O_CREAT, 00644);
		else
			fd = open(node->outfile->name, O_WRONLY | O_TRUNC | O_CREAT, 00644);
		if (fd < 0)
			return (print_file_error(prog_name, node->outfile->name));
		to_free = node->outfile;
		node->outfile = node->outfile->next;
		free(to_free->name);
		free(to_free);
		if (node->outfile)
			close(fd);
	}
	return (fd);
}

int	redirect_output(t_tree *node, int is_child, char *prog_name)
{
	int	fd;

	fd = open_outfile(node, prog_name);
	if (fd < 0)
		return (-1);
	if (is_child && fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror(prog_name);
			close(fd);
			return (-2);
		}
		close(fd);
		return (STDOUT_FILENO);
	}
	return (fd);
}
