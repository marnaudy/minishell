/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:13:47 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 14:36:44 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"
#include <errno.h>
#include <string.h>

static int	free_perror_ret(char *to_free, char *prog_name)
{
	perror(prog_name);
	free(to_free);
	return (-2);
}

int	print_file_error(char *prog_name, char *file_name)
{
	char	*to_print;
	char	*to_free;

	to_print = ft_strcat(": ", strerror(errno));
	if (!to_print)
		return (free_perror_ret(NULL, prog_name));
	to_free = to_print;
	to_print = ft_strcat(file_name, to_print);
	if (!to_print)
		return (free_perror_ret(to_free, prog_name));
	free(to_free);
	to_free = to_print;
	to_print = ft_strcat(": ", to_print);
	if (!to_print)
		return (free_perror_ret(to_free, prog_name));
	free(to_free);
	to_free = to_print;
	to_print = ft_strcat(prog_name, to_print);
	if (!to_print)
		return (free_perror_ret(to_free, prog_name));
	free(to_free);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	write(STDERR_FILENO, "\n", 1);
	free(to_print);
	return (-1);
}
