/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:21:43 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/27 15:35:36 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static void	exec_subshell_in_child(t_tree *node, t_general_info *info)
{
	int	ret;

	if (redirect(node, info))
		exit_wait_child(info, 1);
	ret = exec_node(node->left, info, 1);
	if (ret)
		exit_wait_child(info, ret);
	exit_wait_child(info, info->exit_code);
}

int	exec_subshell_node(t_tree *node, t_general_info *info, int is_child)
{
	int	pid;

	if (is_child)
		exec_subshell_in_child(node, info);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		exec_subshell_in_child(node, info);
	wait_child(pid, info);
	return (0);
}
