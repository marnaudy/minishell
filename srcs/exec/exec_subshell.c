/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:21:43 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:59 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static void	exec_subshell_in_child(t_tree *node, t_general_info *info)
{
	int	ret;

	ret = redirect_input(node, 1, info);
	if (ret < 0)
		exit_wait_child(info, ret);
	ret = redirect_output(node, 1, info->prog_name);
	if (ret < 0)
		exit_wait_child(info, ret);
	ret = exec_node(node->left, info, 1);
	if (ret)
		exit_wait_child(info, ret);
	exit_wait_child(info, info->exit_code);
}

int	exec_subshell_node(t_tree *node, t_general_info *info, int is_child)
{
	int	ret;
	int	pid;

	ret = expand_node(node, info);
	if (ret)
		return (exit_command_node(info, is_child, ret));
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
