/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:25:32 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 16:50:00 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	is_option_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	echo(t_tree *node, int fd_out)
{
	int		option;
	t_list	*list;

	list = node->arg->next;
	option = 0;
	while (list && ((char *)list->content)[0] == '-'
			&& ((char *)list->content)[1]
			&& is_option_n((char *)list->content) && ++option)
		list = list->next;
	while (list)
	{
		write(fd_out, list->content, ft_strlen(list->content));
		if (list->next)
			write(fd_out, " ", 1);
		list = list->next;
	}
	if (!option)
		write (fd_out, "\n", 1);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (0);
}
