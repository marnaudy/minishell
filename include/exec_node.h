/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:38:31 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 14:49:27 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_NODE_H
# define EXEC_NODE_H

# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>

int		expand_args(t_tree *node, t_general_info *info);
int		expand_redirect(t_redirect_list *redirect, t_general_info *info);
int		print_file_error(char *prog_name, char *file_name);
int		open_redirects(t_tree *node, t_general_info *info,
			int *fd_in, int *fd_out);
int		redirect(t_tree *node, t_general_info *info);
int		split_and_wildcard_file(t_tree *node, char *prog_name);
int		print_ambiguous_redirect(char *token, char *prog_name);
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
int		echo(t_tree *node, int fd_out);
int		unset(t_tree *node, t_general_info *info, int fd_out);
int		env(t_general_info *info, int fd_out);
void	sort_env_arr(t_env_list *arr, int size);
int		display_export_env(t_general_info *info, int fd_out);
int		export(t_tree *node, int fd_out, t_general_info *info);
int		pwd(int fd_out, t_general_info *info);
int		exit_builtin(t_tree *node, int fd_out, t_general_info *info);
int		cd(t_tree *node, t_general_info *info, int fd_out);
int		update_pwd(t_general_info *info);
void	wait_child(int pid, t_general_info *info);

#endif
