/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:33:10 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/01 18:59:52 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"
#include <signal.h>

void	print_nl(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	set_signals_wait(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL))
	{
		perror(NULL);
		return (-1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL))
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

void	wait_child(int pid)
{
	int	status;
	int	sig;

	set_signals_wait();
	if (waitpid(pid, &status, 0) < 0)
		perror(NULL);
	if (WIFSIGNALED(status) > 0)
	{
		sig = WTERMSIG(status);
		g_exit_code = 128 + sig;
		if (sig == SIGBUS)
			write(STDERR_FILENO, "Bus error (core dumped)\n", 24);
		if (sig == SIGSEGV)
			write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
		if (sig == SIGABRT)
			write(STDERR_FILENO, "Aborted (core dumped)\n", 22);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		return ;
	}
	g_exit_code = WEXITSTATUS(status);
}
