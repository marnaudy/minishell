/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:24:30 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/27 16:05:40 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	print_ambiguous_redirect(char *token, char *prog_name)
{
	int		len;
	char	*to_print;

	len = ft_strlen(prog_name) + ft_strlen(token)
		+ ft_strlen(": : ambiguous redirect\n") + 1;
	to_print = ft_calloc(len, sizeof(char));
	if (!to_print)
	{
		perror(prog_name);
		return (-1);
	}
	ft_strlcpy(to_print, prog_name, len);
	ft_strlcat(to_print, ": ", len);
	ft_strlcat(to_print, token, len);
	ft_strlcat(to_print, ": ambiguous redirect\n", len);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	return (1);
}
