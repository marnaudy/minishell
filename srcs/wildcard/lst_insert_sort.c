/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_insert_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:31:06 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 20:14:45 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	advanced_ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && ft_toupper(s1[i]) == ft_toupper(s2[i]))
		i++;
	return (ft_toupper(s1[i]) - ft_toupper(s2[i]));
}

void	lst_insert_sort(t_list **list, t_list *new)
{
	if (!*list)
	{
		*list = new;
		return ;
	}
	if (advanced_ft_strcmp((char *)(*list)->content, (char *)new->content) > 0)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	lst_insert_sort(&(*list)->next, new);
}
