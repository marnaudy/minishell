/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:24:13 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 15:33:13 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "environment.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>

typedef struct s_doc_list
{
	char				*content;
	int					is_quoted;
	struct s_doc_list	*next;
}	t_doc_list;

enum e_operator
{
	nothing,
	infile,
	outfile,
	appendout,
	here_doc,
	open_p,
	close_p,
	and,
	or,
	conduit
};

typedef struct s_tree
{
	enum e_operator	type;
	t_list			*arg;
	char			*infile;
	char			*outfile;
	short int		append_output;
	t_doc_list		*here_doc;
	struct s_tree	**pipe_children;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_general_info
{
	char			*prog_name;
	t_hash_table	*table;
	t_tree			*root;
	int				exit_code;
}	t_general_info;

int				free_and_ret(char *s1, char *s2, int ret);
int				is_escaped(char *str, int pos);
int				lexer(t_list **list, char *input, char *prog_name);
int				check_syntax(t_list *token_list, char *prog_name);
t_hash_table	*init_env_table(char **envp);
void			free_hash_table(t_hash_table *table);
int				add_to_table(t_hash_table *table, char *key, char *value);
char			*fetch_value(t_hash_table *table, char *key);
int				remove_value(t_hash_table *table, char *key);
int				is_valid_parameter(char *parameter, int len);
int				skip_simple_quote(char *input, int idx, int *token_len);
int				skip_quote(char *input, int idx, int *token_len);
int				replace_all_parameters(char **str, t_general_info *info,
					int ignore_quotes);
int				quote_removal(char *token, char *prog_name);
void			ft_doc_lstclear(t_doc_list **lst);
int				read_all_here_docs(t_list *token_list, char *prog_name,
					int nb_token, t_doc_list **doc_list);
enum e_operator	operator_type(char *token);
void			free_tree(t_tree **tree);
int				parser(t_tree **root, t_list **tk_list,
					t_doc_list **doc_list, char *prog_name);
void			print_tree(t_tree *tree);
int				field_splitting(t_list **list, char *prog_name);
int				expand_wildcards(t_list *list, char *prog_name);
int				search_path(char *arg0, char **path,
					t_hash_table *table, char *prog_name);
int				expand_node(t_tree *node, t_general_info *info);
int				free_perror_and_ret(void *to_free, char *prog_name,
					int print_error, int ret);
int				exec_node(t_tree *node, t_general_info *info, int is_child);
char			*get_input(char *prog_name);
t_general_info	*free_general_info(t_general_info *info);
t_general_info	*init_info(char *arg0, char **envp);

#endif
