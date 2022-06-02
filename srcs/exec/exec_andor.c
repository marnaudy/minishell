/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_andor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:13:58 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 12:11:46 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	exec_andor_node(t_tree *node, t_general_info *info)
{
	if (exec_node(node->left, info, 0))
		return (-1);
	if (g_exit_code == 130)
		return (0);
	if ((info->exit_code == 0 && node->type == or)
		|| (info->exit_code && node->type == and))
		return (0);
	if (exec_node(node->right, info, 0))
		return (-1);
	return (0);
}
