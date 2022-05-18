/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:38:31 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/18 15:36:06 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_NODE_H
# define EXEC_NODE_H

# include "minishell.h"
# include <fcntl.h>

int	print_file_error(char *prog_name, char *file_name);
int	redirect_input(t_tree *node, int is_child,
		t_tree *root, t_general_info *info);
int	redirect_output(t_tree *node, int is_child, char *prog_name);
int	print_ambiguous_redirect(char *prog_name);

#endif
