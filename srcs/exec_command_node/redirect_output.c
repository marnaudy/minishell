/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:37:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/19 12:01:06 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	redirect_output(t_tree *node, int is_child, char *prog_name)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (node->outfile && node->append_output)
		fd = open(node->outfile, O_WRONLY | O_APPEND | O_CREAT, 00644);
	if (node->outfile && !node->append_output)
		fd = open(node->outfile, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	if (fd < 0)
		return (print_file_error(prog_name, node->outfile));
	if (is_child && node->outfile)
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
