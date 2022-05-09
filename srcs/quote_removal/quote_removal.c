/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:20:16 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 17:18:13 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_removal.h"

static void	free_int_list(t_int_list *list)
{
	t_int_list	*to_free;

	while (list != NULL)
	{
		to_free = list;
		list = list->next;
		free(to_free);
	}
}

static int	char_to_remove(char *str, t_int_list **list, char *prog_name)
{
	int			i;
	t_int_list	*new;

	*list = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_is_in_charset(str[i], "\\\'\"") && !is_escaped(str, i))
		{
			new = malloc(sizeof(t_int_list));
			if (!new)
			{
				perror(prog_name);
				free_int_list(*list);
				*list = NULL;
				return (-1);
			}
			new->nb = i;
			new->next = *list;
			*list = new;
		}
		i++;
	}
	return (0);
}

int	quote_removal(char *token, char *prog_name)
{
	t_int_list	*list;
	t_int_list	*to_free;
	int			i;

	if (char_to_remove(token, &list, prog_name))
		return (-1);
	to_free = list;
	while (list != NULL)
	{
		i = list->nb;
		while (token[i + 1])
		{
			token[i] = token[i + 1];
			i++;
		}
		token[i] = token[i + 1];
		list = list->next;
	}
	free_int_list(to_free);
	return (0);
}
