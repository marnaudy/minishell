/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:06:50 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 20:48:04 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

unsigned int	len_b4_slash(char *str)
{
	unsigned int	len;

	len = 0;
	while (str[len] && str[len] != '/')
		len++;
	return (len);
}

int	substitute_star(char *word, char *to_match)
{
	int		i;
	int		j;

	i = 0;
	if (word[0] == '\0' || word[0] == '/')
		return (ft_strlen(to_match));
	while (to_match[i])
	{
		j = 0;
		while (to_match[i + j] && word[j] == to_match[i + j] && word[j] != '/')
			j++;
		if (!word[j] || (word[j] == '/' && !to_match[i + j]))
			return (i);
		i++;
	}
	return (-1);
}

int	is_match(t_wc_token *list, char *to_match)
{
	int	i;

	if (to_match[0] == '.' && list->is_wc)
		return (0);
	i = 0;
	while (list)
	{
		if (!list->is_wc)
		{
			if (ft_strncmp(to_match + i, list->text, len_b4_slash(list->text)))
				return (0);
			i += len_b4_slash(list->text);
			if (len_b4_slash(list->text) < ft_strlen(list->text))
				return (1);
			list = list->next;
			continue ;
		}
		if (!list->next)
			return (1);
		if (substitute_star(list->next->text, to_match + i) < 0)
			return (0);
		i += substitute_star(list->next->text, to_match + i);
		list = list->next;
	}
	return (!to_match[i]);
}
