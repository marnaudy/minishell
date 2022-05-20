/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:25:32 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 18:01:52 by marnaudy         ###   ########.fr       */
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

static int	open_files_echo(int *fd_out,
				t_general_info *info, t_tree *node)
{
	int	fd_in;

	fd_in = redirect_input(node, 0, info);
	if (fd_in < 0)
		return (-1);
	*fd_out = redirect_output(node, 0, info->prog_name);
	if (*fd_out < 0)
	{
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		return (-1);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	return (0);
}

int	echo(t_tree *node, t_general_info *info)
{
	int		fd_out;
	int		option;
	t_list	*list;

	if (open_files_echo(&fd_out, info, node))
		return (-1);
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
