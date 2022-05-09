/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:34:28 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 15:02:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

int	add_backslash(char **token, int start, int len)
{
	int		i;
	int		j;
	char	*new_token;

	i = start;
	j = 0;
	while (i < start + len)
	{
		if (ft_is_in_charset((*token)[i + j], "\'\"\\")
			&& !is_escaped(*token, i + j))
		{
			new_token = replace_in_str(*token, i + j, 0, "\\");
			if (!new_token)
				return (-1);
			free(*token);
			*token = new_token;
			j++;
		}
		i++;
	}
	return (0);
}
