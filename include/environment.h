/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:19:26 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/04 16:43:50 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include "../libft/libft.h"

# define HASH_TABLE_SIZE 10007

typedef struct s_key_val_pair
{
	char					*key;
	char					*value;
}	t_key_val_pair;

typedef struct s_hash_table
{
	t_key_val_pair		data[HASH_TABLE_SIZE];
	struct s_hash_table	*next;
}	t_hash_table;

void	free_key_value_pair(t_key_val_pair *data);
void	free_hash_table(t_hash_table *table);
int		add_to_table(t_hash_table *table, char *key, char *value);

#include <stdio.h>

#endif
