/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:24:30 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/18 15:38:50 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	print_ambiguous_redirect(char *prog_name)
{
	char	*to_print;

	to_print = ft_strcat(prog_name, ": ambiguous redirect\n");
	if (!to_print)
		return (-1);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	return (1);
}
