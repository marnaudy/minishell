/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:28:03 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 11:40:08 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	free_env_pair(t_env_list *to_free)
{
	free(to_free->key);
	free(to_free->value);
	free(to_free);
}

void	free_env_list(t_env_list **list)
{
	t_env_list	*to_free;
	t_env_list	*iter;

	iter = *list;
	while (iter)
	{
		to_free = iter;
		iter = iter->next;
		free(to_free->key);
		free(to_free->value);
		free(to_free);
	}
	*list = NULL;
}
