/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:45:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 14:47:39 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

void	swap_pair(t_env_list *a, t_env_list *b)
{
	char	*tmp;

	tmp = a->key;
	a->key = b->key;
	b->key = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

void	sort_env_arr(t_env_list *arr, int size)
{
	int	i;
	int	j;
	int	smallest;

	i = 0;
	while (i < size - 1)
	{
		j = i;
		smallest = i;
		while (j < size)
		{
			if (ft_strcmp(arr[j].key, arr[smallest].key) < 0)
				smallest = j;
			j++;
		}
		swap_pair(&arr[i], &arr[smallest]);
		i++;
	}
}
