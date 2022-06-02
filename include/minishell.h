/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:24:13 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 19:26:30 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define _GNU_SOURCE

extern int	g_exit_code;

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

typedef struct s_redirect_list
{
	char					*content;
	int						is_quoted;
	enum e_operator			type;
	struct s_redirect_list	*next;
}	t_redirect_list;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	int					export;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_tree
{
	enum e_operator	type;
	t_list			*arg;
	t_redirect_list	*redirects;
	struct s_tree	**pipe_children;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_general_info
{
	char			*prog_name;
	t_env_list		*env;
	t_tree			*root;
	int				exit_code;
	char			*cwd;
}	t_general_info;

int				is_blank(char c);
int				free_and_ret(char *s1, char *s2, int ret);
int				is_escaped(char *str, int pos);
int				lexer(t_list **list, char *input, char *prog_name);
int				check_syntax(t_list *token_list, char *prog_name);
int				init_env_list(char **envp, t_general_info *info);
void			free_env_list(t_env_list **list);
int				add_to_env(t_general_info *info, char *key,
					char *value, int export);
char			*fetch_value(t_env_list *list, char *key);
int				remove_value(t_env_list **list, char *key);
int				export_env(t_general_info *info,
					char ***env_arr, char *underscore);
int				free_char_array_and_ret(char **arr, int ret);
int				is_valid_parameter(char *parameter, int len);
int				skip_simple_quote(char *input, int idx, int *token_len);
int				skip_quote(char *input, int idx, int *token_len);
int				replace_all_parameters(char **str, t_general_info *info,
					int ignore_quotes);
int				quote_removal(char *token, char *prog_name);
void			ft_redirect_lstadd_back(t_redirect_list **alst,
					t_redirect_list *new);
void			ft_redirect_lstclear(t_redirect_list **lst);
int				read_all_here_docs(t_list *token_list, char *prog_name,
					int nb_token, t_redirect_list **doc_list);
int				launch_here_doc_writer(char *here_doc, t_general_info *info);
enum e_operator	operator_type(char *token);
void			free_tree(t_tree **tree);
int				parser(t_tree **root, t_list **tk_list,
					t_redirect_list **doc_list, char *prog_name);
void			print_tree(t_tree *tree);
int				field_splitting(t_list **list, char *prog_name);
int				expand_wildcards(t_list *list, char *prog_name);
int				search_path(char *arg0, char **path,
					t_env_list *env_list, char *prog_name);
int				free_perror_and_ret(void *to_free, char *prog_name,
					int print_error, int ret);
int				exec_node(t_tree *node, t_general_info *info, int is_child);
char			*get_input(char *prog_name);
int				disable_stdout(char *prog_name);
int				restore_stdout(int fd_save, char *prog_name);
t_general_info	*free_general_info(t_general_info *info);
t_general_info	*init_info(char *arg0, char **envp);
char			*ft_strcat_with_slash(char *s1, char *s2);
int				init_signals_read(char *prog_name);
int				set_signals_exec(char *prog_name);
int				add_backslash(char **token, int start, int len);

#endif
