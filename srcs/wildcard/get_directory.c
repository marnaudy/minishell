/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:43:39 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/16 12:19:09 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	do_nothing(void *nothing)
{
	(void) nothing;
}

static int	dup_and_add_list(t_list	**list, char *str)
{
	t_list	*new_node;
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
		return (-1);
	new_node = ft_lstnew(new_str);
	if (!new_node)
	{
		free(new_str);
		return (-1);
	}
	ft_lstadd_front(list, new_node);
	return (0);
}

int	get_directory(t_list **dir_list)
{
	DIR				*dirp;
	struct dirent	*dir_content;

	*dir_list = NULL;
	dirp = opendir(".");
	if (!dirp)
		return (0);
	dir_content = readdir(dirp);
	while (dir_content)
	{
		if (dup_and_add_list(dir_list, dir_content->d_name))
		{
			ft_lstclear(dir_list, &do_nothing);
			return (-1);
		}
		dir_content = readdir(dirp);
	}
	closedir(dirp);
	return (0);
}
