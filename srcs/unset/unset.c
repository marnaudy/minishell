/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:45:07 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 16:54:36 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_tree *node, t_general_info *info, int fd_out)
{
	t_list	*list;

	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	list = node->arg->next;
	while (list)
	{
		remove_value(&info->env, (char *)list->content);
		list = list->next;
	}
	return (0);
}
