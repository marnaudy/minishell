/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:28:03 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/04 17:01:39 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	free_key_value_pair(t_key_val_pair *data)
{
	free(data->key);
	free(data->value);
	data->key = NULL;
}

void	free_hash_table(t_hash_table *table)
{
	t_hash_table	*to_free;
	int				i;

	while (table)
	{
		to_free = table;
		table = table->next;
		i = 0;
		while (i < HASH_TABLE_SIZE)
		{
			free_key_value_pair(&to_free->data[i]);
			i++;
		}
		free(to_free);
	}
}
