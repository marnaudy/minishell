/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:43:58 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 12:35:04 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static char	*prepare_exec(t_tree *node, t_general_info *info, char ***argv)
{
	int		ret;
	char	*path;

	ret = redirect_input(node, 1, info);
	if (ret < 0)
		exit_wait_child(info, ret);
	ret = redirect_output(node, 1, info->prog_name);
	if (ret < 0)
		exit_wait_child(info, ret);
	if (!node->arg)
		exit_wait_child(info, 0);
	*argv = list_to_tab(node->arg, info->prog_name);
	if (*argv == NULL)
		exit_wait_child(info, -1);
	ret = search_path((char *) node->arg->content,
			&path, info->table, info->prog_name);
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
	char	*path;

	path = prepare_exec(node, info, &argv);
	execv(path, argv);
	perror(info->prog_name);
	if (path != argv[0])
		free(path);
	free(argv);
	exit_wait_child(info, -1);
}

int	expand_exec_command_node(t_tree *node, t_general_info *info, int is_child)
{
	int	ret;
	int	pid;

	ret = expand_node(node, info);
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
	waitpid(pid, &ret, 0);
	info->exit_code = WEXITSTATUS(ret);
	return (0);
}
