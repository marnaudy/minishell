/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:00:24 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 17:28:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static int	open_files_builtin(int *fd_out,
				t_general_info *info, t_tree *node)
{
	int	fd_in;

	fd_in = redirect_input(node, 0, info);
	if (fd_in < 0)
		return (-1);
	*fd_out = redirect_output(node, 0, info->prog_name);
	if (*fd_out < 0)
	{
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		return (-1);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	return (0);
}

int	is_builtin(t_tree *node)
{
	if (!node->arg)
		return (0);
	return (!ft_strcmp((char *)node->arg->content, "echo")
		|| !ft_strcmp((char *)node->arg->content, "cd")
		|| !ft_strcmp((char *)node->arg->content, "pwd")
		|| !ft_strcmp((char *)node->arg->content, "export")
		|| !ft_strcmp((char *)node->arg->content, "unset")
		|| !ft_strcmp((char *)node->arg->content, "env")
		|| !ft_strcmp((char *)node->arg->content, "exit"));
}

int	launch_builtin(t_tree *node, t_general_info *info)
{
	int	fd_out;

	if (open_files_builtin(&fd_out, info, node))
		return (-1);
	if (!ft_strcmp((char *)node->arg->content, "echo"))
		return (echo(node, fd_out));
	if (!ft_strcmp((char *)node->arg->content, "unset"))
		return (unset(node, info, fd_out));
	if (!ft_strcmp((char *)node->arg->content, "env"))
		return (env(info, fd_out));
	puts("Nothing to see here\n");
	return (0);
}
