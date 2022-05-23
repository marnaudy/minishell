/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:30:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 13:58:18 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	add_to_env(t_general_info *info, char *key, char *value, int export)
{
	t_env_list	*new_pair;
	t_env_list	*iter;

	new_pair = malloc(sizeof(t_env_list));
	if (!new_pair)
	{
		perror(info->prog_name);
		return (-1);
	}
	new_pair->key = key;
	new_pair->value = value;
	new_pair->export = export;
	new_pair->next = NULL;
	if (info->env == NULL)
	{
		info->env = new_pair;
		return (0);
	}
	iter = info->env;
	while (iter->next)
		iter = iter->next;
	iter->next = new_pair;
	return (0);
}

char	*fetch_value(t_env_list *list, char *key)
{
	while (list)
	{
		if (!ft_strcmp(key, list->key))
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

int	remove_value(t_env_list **list, char *key)
{
	t_env_list	*iter;
	t_env_list	*to_free;

	if (*list && !ft_strcmp((*list)->key, key))
	{
		to_free = *list;
		*list = (*list)->next;
		free_env_pair(to_free);
		return (0);
	}
	iter = *list;
	while (iter->next)
	{
		if (!ft_strcmp(iter->next->key, key))
		{
			to_free = iter->next;
			iter->next = iter->next->next;
			free_env_pair(to_free);
			return (0);
		}
		iter = iter->next;
	}
	return (1);
}
