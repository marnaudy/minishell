/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:14:18 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 16:54:44 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

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

long int	get_exit_code(t_list *arg, t_general_info *info)
{
	char		*arg1;
	long int	res;

	if (!arg)
		return (info->exit_code);
	arg1 = (char *)arg->content;
	if (!is_numeric_argument(arg1) || ft_atol(arg1, &res))
	{
		ft_putstr_fd(info->prog_name, STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(arg1, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_general_info(info);
		exit(2);
	}
	return (res);
}

int	exit_builtin(t_tree *node, int fd_out, t_general_info *info)
{
	long int		exit_code;
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
	char_exit_code = (unsigned char) exit_code;
	exit_code = (long int) char_exit_code;
	exit(exit_code);
	return (0);
}
