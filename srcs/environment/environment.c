/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:30:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 16:03:57 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	add_pair_back(t_env_list **list, t_env_list *new)
{
	t_env_list	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_pair_to_list(t_env_list **list, t_env_list *new)
{
	t_env_list	*iter;

	iter = *list;
	while (iter)
	{
		if (!ft_strcmp(iter->key, new->key))
		{
			free(iter->value);
			iter->value = new->value;
			iter->export = new->export;
			free(new->key);
			free(new);
			return ;
		}
		iter = iter->next;
	}
	add_pair_back(list, new);
}

int	add_to_env(t_general_info *info, char *key, char *value, int export)
{
	t_env_list	*new_pair;

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
	add_pair_to_list(&info->env, new_pair);
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
	while (iter && iter->next)
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
