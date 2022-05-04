/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:30:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/04 16:28:00 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static unsigned int	hash_function(const char *key)
{
	int				i;
	unsigned int	hash;

	i = 0;
	hash = 0;
	while (key[i] != '\0')
	{
		hash += key[i];
		hash += hash << 10;
		hash ^= hash >> 6;
		i++;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	hash %= HASH_TABLE_SIZE;
	return (hash);
}

int	add_to_table(t_hash_table *table, char *key, char *value)
{
	unsigned int	hash;

	hash = hash_function(key);
	if (table->data[hash].key && ft_strcmp(key, table->data[hash].key))
	{
		if (table->next == NULL)
		{
			table->next = ft_calloc(sizeof(t_hash_table), 1);
			if (table->next == NULL)
				return (-1);
		}
		return (add_to_table(table->next, key, value));
	}
	table->data[hash].key = key;
	table->data[hash].value = value;
	return (0);
}

char	*fetch_value(t_hash_table *table, char *key)
{
	unsigned int	hash;

	hash = hash_function(key);
	while (table)
	{
		if (table->data[hash].key && !ft_strcmp(table->data[hash].key, key))
			return (table->data[hash].value);
		table = table->next;
	}
	return (NULL);
}

int	remove_value(t_hash_table *table, char *key)
{
	unsigned int	hash;

	hash = hash_function(key);
	while (table)
	{
		if (table->data[hash].key && !ft_strcmp(table->data[hash].key, key))
		{
			free_key_value_pair(&table->data[hash]);
			return (0);
		}
		table = table->next;
	}
	return (1);
}
