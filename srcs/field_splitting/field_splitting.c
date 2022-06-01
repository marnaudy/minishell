/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:40:53 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 15:39:19 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_white_space(char *str, char **new_str, char *prog_name)
{
	int	i;

	*new_str = NULL;
	i = 0;
	while (ft_is_in_charset(str[i], " \t\n"))
		i++;
	if (str[i] == '\0')
		return (0);
	*new_str = ft_strdup(&str[i]);
	if (!new_str)
	{
		perror(prog_name);
		return (-1);
	}
	return (0);
}

static int	split_add_to_list(t_list *list, int index, char *prog_name)
{
	char	*word;
	char	*new_word;
	t_list	*new_link;

	word = (char *) list->content;
	if (trim_white_space(&word[index], &new_word, prog_name))
		return (-1);
	word[index] = '\0';
	if (new_word == NULL)
		return (0);
	new_link = ft_lstnew(new_word);
	if (!new_link)
	{
		perror(prog_name);
		free(new_word);
		return (-1);
	}
	new_link->next = list->next;
	list->next = new_link;
	return (0);
}

static int	split_word(t_list *list, char *prog_name)
{
	char	*word;
	int		i;

	word = (char *) list->content;
	i = 0;
	while (word[i])
	{
		if (ft_is_in_charset(word[i], " \t\n") && !is_escaped(word, i))
		{
			if (split_add_to_list(list, i, prog_name))
				return (-1);
			return (0);
		}
		i++;
	}
	return (0);
}

static void	remove_empty_tokens(t_list **list)
{
	char	*str;
	t_list	*to_free;
	t_list	*temp;

	while (*list && !((char *)(*list)->content)[0])
	{
		to_free = *list;
		*list = (*list)->next;
		free(to_free->content);
		free(to_free);
	}
	temp = *list;
	while (temp && temp->next)
	{
		str = (char *)temp->next->content;
		if (!str[0])
		{
			to_free = temp->next;
			temp->next = temp->next->next;
			free(to_free->content);
			free(to_free);
		}
		temp = temp->next;
	}
}

int	field_splitting(t_list **list, char *prog_name)
{
	t_list	*temp;

	temp = *list;
	while (temp)
	{
		if (split_word(temp, prog_name))
			return (-1);
		temp = temp->next;
	}
	if (*list)
		remove_empty_tokens(list);
	return (0);
}
