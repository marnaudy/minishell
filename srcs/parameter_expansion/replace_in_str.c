/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:02:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 15:01:55 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

// Only sort of protected, 
char	*replace_in_str(char *str, int start, int len, char *to_add)
{
	char	*new;
	int		i;
	int		j;

	new = malloc((ft_strlen(str) - len + ft_strlen(to_add) + 1) * sizeof(char));
	if (!new || ft_strlen(str) < (long unsigned int) start + len)
	{
		free(new);
		return (NULL);
	}
	i = -1;
	while (++i < start && str[i])
		new[i] = str[i];
	j = 0;
	while (to_add && to_add[j])
	{
		new[i + j] = to_add[j];
		j++;
	}
	i--;
	while (str[++i + len])
		new[i + j] = str[i + len];
	new[i + j] = 0;
	return (new);
}
