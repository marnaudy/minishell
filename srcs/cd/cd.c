/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:06:11 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/31 14:34:43 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"
#include "lexer.h"
#include <sys/types.h>
#include <sys/stat.h>

static void	print_no_home(t_general_info *info)
{
	ft_putstr_fd(info->prog_name, STDERR_FILENO);
	ft_putstr_fd(": cd : HOME not set\n", STDERR_FILENO);
}

int	get_destination(char **arg, t_general_info *info, char **dest)
{
	if (!*arg)
	{
		*arg = fetch_value(info->env, "HOME");
		if (!*arg)
		{
			print_no_home(info);
			return (1);
		}
	}
	if ((*arg)[0] == '/')
	{
		*dest = ft_strdup(*arg);
		if (!*dest)
		{
			perror(info->prog_name);
			return (-1);
		}
		return (0);
	}
	*dest = ft_strcat_with_slash(info->cwd, *arg);
	if (!*dest)
		return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
	return (0);
}

static int	check_destination(char *dest, char *prog_name, char *arg0)
{
	struct stat	buf;

	if (!*arg0)
		return (0);
	if (access(dest, F_OK))
	{
		ft_putstr_fd(prog_name, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		ft_putstr_fd(arg0, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	stat(dest, &buf);
	if (!S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(prog_name, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		ft_putstr_fd(arg0, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	too_many_arg(t_tree *node, char *prog_name)
{
	if (node->arg->next && node->arg->next->next
		&& !is_operator((char *) node->arg->next->next->content,
			ft_strlen((char *) node->arg->next->next->content)))
	{
		ft_putstr_fd(prog_name, STDERR_FILENO);
		ft_putstr_fd(": cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	cd(t_tree *node, t_general_info *info, int fd_out)
{
	int		ret;
	char	*dest;
	char	*arg0;

	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	arg0 = NULL;
	if (node->arg->next)
		arg0 = (char *)node->arg->next->content;
	if (too_many_arg(node, info->prog_name))
		return (1);
	ret = get_destination(&arg0, info, &dest);
	if (ret)
		return (ret);
	if (check_destination(dest, info->prog_name, arg0))
		return (free_and_ret(dest, NULL, 1));
	if (chdir(dest) == -1)
		return (free_perror_and_ret(dest, info->prog_name, 1, 1));
	free(info->cwd);
	info->cwd = getcwd(NULL, 0);
	if (!info->cwd)
		return (free_perror_and_ret(dest, info->prog_name, 1, -1));
	if (update_pwd(info))
		return (free_and_ret(dest, NULL, -1));
	return (free_and_ret(dest, NULL, 0));
}
