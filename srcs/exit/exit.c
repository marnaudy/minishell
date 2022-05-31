/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:14:18 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/31 14:47:29 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	is_overflow(int n)
{
	if (n > 2147483647)
		return (1);
	return (0);
}

int	is_numeric_argument(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (is_blank(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_exit_code(t_list *arg, t_general_info *info)
{
	char	*arg1;

	if (!arg)
		return (0);
	arg1 = (char *)arg->content;
	if (!is_numeric_argument(arg1) || !is_overflow(ft_atoi(arg1)))
	{
		ft_putstr_fd(info->prog_name, STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(arg1, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_general_info(info);
		rl_clear_history();
		exit(2);
	}
	return (ft_atoi(arg1));
}

int	exit_builtin(t_tree *node, int fd_out, t_general_info *info)
{
	int				exit_code;
	unsigned char	char_exit_code;

	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	exit_code = get_exit_code(node->arg->next, info);
	if (node->arg->next && node->arg->next->next)
	{
		ft_putstr_fd(info->prog_name, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		if (info->exit_code)
			return (info->exit_code);
		return (1);
	}
	free_general_info(info);
	rl_clear_history();
	char_exit_code = (unsigned char) exit_code;
	exit_code = (int) char_exit_code;
	exit(exit_code);
	return (0);
}
