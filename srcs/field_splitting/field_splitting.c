/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:40:53 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 17:12:19 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_white_space(char *str, char **new_str)
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
		return (-1);
	return (0);
}

static int	split_add_to_list(t_list *list, int index)
{
	char	*word;
	char	*new_word;
	t_list	*new_link;

	word = (char *) list->content;
	if (trim_white_space(&word[index], &new_word))
		return (-1);
	if (new_word == NULL)
		return (0);
	new_link = ft_lstnew(new_word);
	if (!new_link)
	{
		free(new_word);
		return (-1);
	}
	word[index] = '\0';
	new_link->next = list->next;
	list->next = new_link;
	return (0);
}

static int	split_word(t_list *list)
{
	char	*word;
	int		i;

	word = (char *) list->content;
	i = 0;
	while (word[i])
	{
		if (ft_is_in_charset(word[i], " \t\n") && !is_escaped(word, i))
		{
			if (split_add_to_list(list, i))
				return (-1);
			return (0);
		}
		i++;
	}
	return (0);
}

int	field_splitting(t_list *list)
{
	while (list)
	{
		split_word(list);
		list = list->next;
	}
	return (0);
}
