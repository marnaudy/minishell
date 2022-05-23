/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:23:43 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 17:30:28 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	env(t_general_info *info, int fd_out)
{
	char	**envp;
	int		i;

	if (export_env(info, &envp))
		return (-1);
	i = 0;
	while (envp[i])
	{
		write(fd_out, envp[i], ft_strlen(envp[i]));
		write(fd_out, "\n", 1);
		free(envp[i]);
		i++;
	}
	free(envp);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (0);
}
