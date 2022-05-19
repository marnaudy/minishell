/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:11:21 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/19 16:26:04 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	exec_node(t_tree *node, t_general_info *info, int is_child)
{
	if (node->type == nothing)
		return (expand_exec_command_node(node, info, is_child));
	if (node->type == and || node->type == or)
		return (exec_andor_node(node, info));
	if (node->type == open_p)
		return (exec_subshell_node(node, info, is_child));
	if (node->type == conduit)
		return (exec_pipe(node, info));
	return (0);
}
