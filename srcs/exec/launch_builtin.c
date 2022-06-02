/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:00:24 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 15:14:13 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static int	open_files_builtin(int *fd_out,
				t_general_info *info, t_tree *node)
{
	int	fd_in;
	int	ret;

	ret = open_redirects(node, info, &fd_in, fd_out);
	if (ret)
		return (ret);
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
	int	ret;

	ret = open_files_builtin(&fd_out, info, node);
	if (ret)
		return (ret);
	if (!ft_strcmp((char *)node->arg->content, "echo"))
		return (echo(node, fd_out));
	if (!ft_strcmp((char *)node->arg->content, "unset"))
		return (unset(node, info, fd_out));
	if (!ft_strcmp((char *)node->arg->content, "env"))
		return (env(info, fd_out));
	if (!ft_strcmp((char *)node->arg->content, "export"))
		return (export(node, fd_out, info));
	if (!ft_strcmp((char *)node->arg->content, "pwd"))
		return (pwd(fd_out, info));
	if (!ft_strcmp((char *)node->arg->content, "exit"))
		return (exit_builtin(node, fd_out, info));
	if (!ft_strcmp((char *)node->arg->content, "cd"))
		return (cd(node, info, fd_out));
	return (0);
}
