/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:12:12 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/24 15:46:20 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	pwd(int fd_out, t_general_info *info)
{
	char	*pwd;

	if (info->cwd)
	{
		write(fd_out, info->cwd, ft_strlen(info->cwd));
		write(fd_out, "\n", 1);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror(info->prog_name);
		return (1);
	}
	write(fd_out, pwd, ft_strlen(pwd));
	write(fd_out, "\n", 1);
	free(pwd);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (0);
}
