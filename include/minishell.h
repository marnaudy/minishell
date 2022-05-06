/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:24:13 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/06 10:52:45 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "environment.h"

typedef struct s_general_info
{
	char			*prog_name;
	t_hash_table	*table;
	int				exit_code;
}	t_general_info;

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
int				replace_all_parameters(char **str, t_general_info *info);

#endif
