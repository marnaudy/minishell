/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:06:50 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/16 11:52:31 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	substitute_star(char *word, char *to_match)
{
	int		i;
	int		j;

	i = 0;
	if (word[0] == '\0')
		return (ft_strlen(to_match));
	while (to_match[i])
	{
		j = 0;
		while (to_match[i + j] && word[j] == to_match[i + j] && word[j] != '*')
			j++;
		if (word[j] == '*' || (!word[j] && !to_match[i + j]))
			return (i);
		i++;
	}
	return (-1);
}

int	is_match(char *word, char *to_match)
{
	int	i;
	int	j;

	if (word[0] != '.' && to_match[0] == '.')
		return (0);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '*' && !is_escaped(word, i))
		{
			i++;
			if (substitute_star(word + i, to_match + j) == -1)
				return (0);
			j += substitute_star(word + i, to_match + j);
			continue ;
		}
		if (word[i] != to_match[j])
			return (0);
		j++;
		i++;
	}
	return (!word[i] && !to_match[j]);
}
