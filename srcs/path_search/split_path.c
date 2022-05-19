/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:20:13 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/19 12:48:57 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_search.h"

static int	nb_string(char const *s)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (s[i])
	{
		if (s[i] == ':')
			nb++;
		i++;
	}
	return (nb);
}

static char	**check_array(char **array, int size)
{
	int	i;
	int	is_good;

	i = 0;
	is_good = 1;
	while (i < size)
	{
		is_good = (is_good && array[i]);
		i++;
	}
	if (is_good)
		return (array);
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**perror_and_return(char *prog_name)
{
	perror(prog_name);
	return (NULL);
}

char	**split_path(char const *s, char *prog_name)
{
	int		i;
	int		j;
	int		arr_idx;
	char	**array;

	array = malloc(sizeof(char *) * (nb_string(s) + 1));
	if (!array)
		return (perror_and_return(prog_name));
	i = 0;
	arr_idx = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] != ':' && s[i + j])
			j++;
		array[arr_idx++] = ft_substr(s, i, j);
		if (!array[arr_idx - 1])
			perror(prog_name);
		i += j;
		i += (s[i] && !(s[i] == ':' && !s[i + 1] && j));
	}
	array[arr_idx] = NULL;
	return (check_array(array, nb_string(s)));
}
