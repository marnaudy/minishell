/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:43:58 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 15:25:41 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static char	*prepare_exec(t_tree *node, t_general_info *info, char ***argv)
{
	int		ret;
	char	*path;

	if (redirect(node, info))
		exit_wait_child(info, 1);
	if (!node->arg)
		exit_wait_child(info, 0);
	*argv = list_to_tab(node->arg, info->prog_name);
	if (*argv == NULL)
		exit_wait_child(info, -1);
	ret = search_path((char *) node->arg->content,
			&path, info->env, info->prog_name);
	if (ret)
	{
		free(*argv);
		exit_wait_child(info, ret);
	}
	return (path);
}

void	exec_command_node(t_tree *node, t_general_info *info)
{
	char	**argv;
	char	**envp;
	char	*path;

	path = prepare_exec(node, info, &argv);
	if (export_env(info, &envp, path))
		exit_command_node(info, 1, -1);
	execve(path, argv, envp);
	perror(info->prog_name);
	if (path != argv[0])
		free(path);
	free(argv);
	free_char_array_and_ret(envp, 0);
	exit_wait_child(info, -1);
}

int	expand_exec_command_node(t_tree *node, t_general_info *info, int is_child)
{
	int	ret;
	int	pid;

	ret = expand_args(node, info);
	if (ret)
		return (exit_command_node(info, is_child, ret));
	if (is_builtin(node))
		return (exit_command_node(info, is_child,
				launch_builtin(node, info)));
	if (is_child)
		exec_command_node(node, info);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		exec_command_node(node, info);
	wait_child(pid, info);
	return (0);
}
