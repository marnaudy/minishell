/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:46:06 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/13 17:33:44 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*join_path(char *word, char *file, char *prog_name)
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

int	expand_one_wildcard(t_list **list, char *prog_name, t_list *dir_content)
{
	t_list	*expansion;
	t_list	*new_node;
	char	*base_path;
	char	*new_word;

	if (!has_wildcard((char *)(*list)->content))
		return (0);
	expansion = NULL;
	if (get_base_path((char *)(*list)->content, &base_path) == -1)
		return (-1);
	if (!base_path)
		return (0);
	while (dir_content)
	{
		if (is_match(base_path, (char *)dir_content->content))
		{
			new_word = join_path((char *)(*list)->content, (char *)dir_content->content, prog_name);
			if (!new_word)
			{
				ft_lstclear(&expansion, &free);
				free(base_path);
				return (-1);
			}
			new_node = ft_lstnew(new_word);
			if (!new_node)
			{
				ft_lstclear(&expansion, &free);
				free(base_path);
				free(new_word);
				return (-1);
			}
			lst_insert_sort(&expansion, new_node);
		}
		dir_content = dir_content->next;
	}
	free(base_path);
	if (expansion)
	{
		ft_lstadd_back(&expansion, (*list)->next);
		new_node = *list;
		*list = expansion;
		free(new_node);
	}
	return (0);
}

int	expand_wildcards(t_list **list, char *prog_name)
{

}
