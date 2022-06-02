/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:45:07 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 14:07:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_tree *node, t_general_info *info, int fd_out)
{
	t_list	*list;
	int		ret;

	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	list = node->arg->next;
	ret = 0;
	while (list)
	{
		if (is_valid_parameter((char *)list->content, -1))
			remove_value(&info->env, (char *)list->content);
		else
		{
			ft_putstr_fd(info->prog_name, STDERR_FILENO);
			ft_putstr_fd(": unset: `", STDERR_FILENO);
			ft_putstr_fd((char *)list->content, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			ret = 1;
		}
		list = list->next;
	}
	return (ret);
}
