/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:14 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 19:27:54 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_wc_token
{
	int					is_wc;
	char				*text;
	struct s_wc_token	*next;
}	t_wc_token;

int		has_wildcard(char *str);
int		free_lstclr_ret(void *to_free, t_list **list_free, int ret);
void	lst_insert_sort(t_list **list, t_list *new);
int		is_match(t_wc_token *list, char *file_name);
int		get_directory(t_list **dir_list);
int		get_wc_list(t_wc_token **list, char *str, char *prog_name);
int		clear_wc_list_and_ret(t_wc_token **list, int ret,
			int print_err, char *prog_name);
#endif
