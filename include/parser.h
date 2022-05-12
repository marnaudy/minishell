/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:33:32 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 15:05:11 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_tree			*init_tree(char *token, char *prog_name);
void			del_first_token(t_list **token_list);
t_tree			*new_command_node(t_list **token_list, t_doc_list **doc_list,
					char *prog_name);
int				add_andor(t_tree **root, t_list **token_list, char *prog_name);
int				add_pipe(t_tree **working_node, t_list **token_list,
					t_doc_list **doc_list, char *prog_name);
void			add_to_node(t_tree **working_node, t_tree *new_node);
int				add_parentheses(t_tree **root, t_list **token_list,
					t_doc_list **doc_list, char *prog_name);
void			add_redirection(t_tree *node,
					t_list **token_list, t_doc_list **doc_list);

#endif
