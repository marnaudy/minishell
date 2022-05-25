/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:33:10 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/25 16:19:09 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"
#include <signal.h>

void	wait_child(int pid, t_general_info *info)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		info->exit_code = 128 + sig;
		if (sig == SIGBUS)
			write(STDERR_FILENO, "Bus error (core dumped)\n", 24);
		if (sig == SIGSEGV)
			write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
		if (sig == SIGABRT)
			write(STDERR_FILENO, "Aborted (core dumped)\n", 22);
		if (sig == SIGINT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		return ;
	}
	info->exit_code = WEXITSTATUS(status);
}
