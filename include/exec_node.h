/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:38:31 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/19 18:25:37 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_NODE_H
# define EXEC_NODE_H

# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>

int		print_file_error(char *prog_name, char *file_name);
int		redirect_input(t_tree *node, int is_child, t_general_info *info);
int		redirect_output(t_tree *node, int is_child, char *prog_name);
int		print_ambiguous_redirect(char *prog_name);
int		is_builtin(t_tree *node);
int		launch_builtin(t_tree *node, t_general_info *info);
int		exit_command_node(t_general_info *info, int is_child, int ret);
void	exit_wait_child(t_general_info *info, int ret);
char	**list_to_tab(t_list *list, char *prog_name);
int		exec_andor_node(t_tree *node, t_general_info *info);
int		exec_subshell_node(t_tree *node, t_general_info *info, int is_child);
void	close_pipes(int	*pipe_fd, int nb_to_close);
int		*open_pipes(int nb_pipes, char *prog_name);
int		exec_pipe(t_tree *node, t_general_info *info);
int		expand_exec_command_node(t_tree *node, t_general_info *info,
			int is_child);
#endif
