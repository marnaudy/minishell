/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:39:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/05 18:41:48 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

int	bad_sub_message(char *parameter, char *prog_name)
{
	char	*to_print;
	char	*to_free;

	to_free = ft_strcat(prog_name, ": ${");
	if (!to_free)
		return (-1);
	to_print = ft_strcat(to_free, parameter);
	free(to_free);
	to_free = to_print;
	if (!to_print)
		return (-1);
	to_print = ft_strcat(to_print, "}: bad substitution\n");
	free(to_free);
	if (!to_print)
		return (-1);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	return (1);
}
