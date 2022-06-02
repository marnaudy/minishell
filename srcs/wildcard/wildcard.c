/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:46:06 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 15:19:42 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static char	*join_path(char *word, char *file, char *prog_name)
{
	int		i;
	char	*new_path;

	i = 0;
	while (word[i] && word[i] != '/')
		i++;
	new_path = ft_strcat(file, word + i);
	if (!new_path)
		perror(prog_name);
	return (new_path);
}

static void	add_expansion_list_to_list(t_list **list, t_list *expansion)
{
	t_list	*temp_node;

	if (!expansion)
		return ;
	temp_node = expansion;
	while (temp_node->next)
		temp_node = temp_node->next;
	ft_lstadd_back(&expansion, (*list)->next);
	free((*list)->content);
	(*list)->content = expansion->content;
	(*list)->next = expansion->next;
	free(expansion);
	*list = temp_node;
}

static int	add_to_expansion_list(t_list **expansion, char *arg,
		char *dir_content, char *prog_name)
{
	char		*new_word;
	t_list		*new_node;
	struct stat	buf;

	new_word = join_path(arg, dir_content, prog_name);
	if (!new_word)
	{
		ft_lstclear(expansion, &free);
		return (-1);
	}
	if (stat(new_word, &buf))
	{
		free(new_word);
		ft_lstclear(expansion, &free);
		return (0);
	}
	new_node = ft_lstnew(new_word);
	if (!new_node)
	{
		ft_lstclear(expansion, &free);
		free(new_word);
		return (-1);
	}
	lst_insert_sort(expansion, new_node);
	return (0);
}

int	expand_one_wildcard(t_list **list, char *prog_name, t_list *dir_content)
{
	t_list	*expansion;
	char	*base_path;

	if (!has_wildcard((char *)(*list)->content))
		return (0);
	expansion = NULL;
	if (get_base_path((char *)(*list)->content, &base_path) == -1)
		return (-1);
	if (!base_path)
		return (0);
	while (dir_content)
	{
		if (is_match(base_path, (char *)dir_content->content)
			&& add_to_expansion_list(&expansion, (char *)(*list)->content,
			(char *)dir_content->content, prog_name))
		{
			free(base_path);
			return (-1);
		}
		dir_content = dir_content->next;
	}
	free(base_path);
	add_expansion_list_to_list(list, expansion);
	return (0);
}

int	expand_wildcards(t_list *list, char *prog_name)
{
	t_list	*dir_content;

	if (get_directory(&dir_content))
		return (-1);
	while (list)
	{
		if (expand_one_wildcard(&list, prog_name, dir_content))
		{
			ft_lstclear(&dir_content, &free);
			return (-1);
		}
		list = list->next;
	}
	ft_lstclear(&dir_content, &free);
	return (0);
}
