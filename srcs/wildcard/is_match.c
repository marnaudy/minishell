/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:06:50 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/13 12:22:29 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_match(char *base_path, char *file_name)
{
	int	i;

	if (base_path[0] != '.' && file_name[0] == '.')
		return (0);
	i = 0;
	while (base_path[i] != '*' || is_escaped(base_path, i))
	{
		if (base_path[i] != file_name[i])
			return (0);
		if (!base_path[i])
			return (1);
		i++;
	}
	
}
