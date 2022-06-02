/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:13:19 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 12:30:47 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	sig_int_handler_read(int sig)
{
	(void)sig;
	g_exit_code = 130;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int_handler_exec(int sig)
{
	(void)sig;
	g_exit_code = 130;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	sig_quit_handler_exec(int sig)
{
	(void)sig;
	g_exit_code = 131;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("\n", STDERR_FILENO);
}

int	init_signals_read(char *prog_name)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL))
	{
		perror(prog_name);
		return (-1);
	}
	sa.sa_handler = &sig_int_handler_read;
	if (isatty(STDIN_FILENO) && sigaction(SIGINT, &sa, NULL))
	{
		perror(prog_name);
		return (-1);
	}
	return (0);
}

int	set_signals_exec(char *prog_name)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &sig_int_handler_exec;
	if (isatty(STDIN_FILENO) && sigaction(SIGINT, &sa, NULL))
	{
		perror(prog_name);
		return (-1);
	}
	sa.sa_handler = &sig_quit_handler_exec;
	if (sigaction(SIGQUIT, &sa, NULL))
	{
		perror(prog_name);
		return (-1);
	}
	return (0);
}
