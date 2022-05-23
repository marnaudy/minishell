/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:00:24 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 12:55:26 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	is_builtin(t_tree *node)
{
	if (!node->arg)
		return (0);
	return (!ft_strcmp((char *)node->arg->content, "echo")
		|| !ft_strcmp((char *)node->arg->content, "cd")
		|| !ft_strcmp((char *)node->arg->content, "pwd")
		|| !ft_strcmp((char *)node->arg->content, "export")
		|| !ft_strcmp((char *)node->arg->content, "unset")
		|| !ft_strcmp((char *)node->arg->content, "env ")
		|| !ft_strcmp((char *)node->arg->content, "exit"));
}

int	launch_builtin(t_tree *node, t_general_info *info)
{
	if (!ft_strcmp((char *)node->arg->content, "echo"))
		return (echo(node, info));
	puts("Nothing to see here\n");
	return (0);
}
