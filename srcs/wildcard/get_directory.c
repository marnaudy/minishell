/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:43:39 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/13 11:53:20 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	do_nothing(void *nothing)
{
	(void) nothing;
}

t_list	*get_directory(void)
{
	DIR				*dirp;
	struct dirent	*dir_content;
	t_list			*list;
	t_list			*new_list;

	list = NULL;
	dirp = opendir(".");
	if (!dirp)
		return (NULL);
	dir_content = readdir(dirp);
	while (dir_content)
	{
		new_list = ft_lstnew(dir_content->d_name);
		if (!new_list)
		{
			ft_lstclear(&list, &do_nothing);
			return (NULL);
		}
		ft_lstadd_front(&list, new_list);
		dir_content = readdir(dirp);
	}
	closedir(dirp);
	return (list);
}
