/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:46:06 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 20:20:18 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static char	*join_path(t_wc_token *wc_list, char *file, char *prog_name)
{
	int		i;
	char	*new_path;
	char	*word;

	i = 0;
	while (wc_list && (wc_list->is_wc || !ft_is_in_charset('/', wc_list->text)))
		wc_list = wc_list->next;
	if (wc_list)
		word = wc_list->text;
	else
		word = "";
	while (word && word[i] && word[i] != '/')
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
	if (!expansion->next)
	{
		free((*list)->content);
		(*list)->content = expansion->content;
		free(expansion);
		return ;
	}
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

static int	add_to_expansion_list(t_list **expansion, t_wc_token *wc_list,
		char *dir_content, char *prog_name)
{
	char		*new_word;
	t_list		*new_node;
	struct stat	buf;

	new_word = join_path(wc_list, dir_content, prog_name);
	if (!new_word)
	{
		ft_lstclear(expansion, &free);
		return (-1);
	}
	if (stat(new_word, &buf))
		return (free_and_ret(new_word, NULL, 0));
	if (add_backslash(&new_word, 0, ft_strlen(new_word)))
		return (free_lstclr_ret(NULL, expansion, -1));
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

int	expand_one_wildcard(t_list **list, char *prog_name,
		t_list *dir_content, t_wc_token *wc_list)
{
	t_list	*expansion;

	if (!has_wildcard((char *)(*list)->content))
		return (0);
	expansion = NULL;
	while (dir_content)
	{
		if (is_match(wc_list, (char *)dir_content->content)
			&& add_to_expansion_list(&expansion, wc_list,
				(char *)dir_content->content, prog_name))
			return (-1);
		dir_content = dir_content->next;
	}
	add_expansion_list_to_list(list, expansion);
	return (0);
}

int	expand_wildcards(t_list *list, char *prog_name)
{
	t_list		*dir_content;
	t_wc_token	*wc_list;

	if (get_directory(&dir_content))
		return (-1);
	while (list)
	{
		if (get_wc_list(&wc_list, list->content, prog_name))
		{
			ft_lstclear(&dir_content, &free);
			return (-1);
		}
		if (expand_one_wildcard(&list, prog_name, dir_content, wc_list))
		{
			ft_lstclear(&dir_content, &free);
			clear_wc_list_and_ret(&wc_list, 0, 0, 0);
			return (-1);
		}
		if (list)
			list = list->next;
		clear_wc_list_and_ret(&wc_list, 0, 0, 0);
	}
	ft_lstclear(&dir_content, &free);
	return (0);
}
