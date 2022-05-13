/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:25:37 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/13 15:30:02 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	get_base_path(char *word, char **base_path)
{
	int	i;

	i = 0;
	while (word[i] && word[i] != '/')
		i++;
	*base_path = NULL;
	if (i == 0)
		return (0);
	*base_path = ft_strsub(word, 0, i);
	if (!*base_path)
		return (-1);
	return (0);
}
