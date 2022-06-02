/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:38:02 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 16:54:47 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	exit_command_node(t_general_info *info, int is_child, int ret)
{
	if (is_child)
	{
		free_general_info(info);
		exit(ret);
	}
	info->exit_code = ret;
	return (ret);
}

void	exit_wait_child(t_general_info *info, int ret)
{
	close(STDIN_FILENO);
	wait(NULL);
	exit_command_node(info, 1, ret);
}

char	**list_to_tab(t_list *list, char *prog_name)
{
	int		len;
	char	**tab;
	int		i;

	len = ft_lstsize(list);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
	{
		perror(prog_name);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		tab[i] = (char *) list->content;
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
