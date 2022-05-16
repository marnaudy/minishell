/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:14 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/16 12:10:39 by marnaudy         ###   ########.fr       */
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

int		has_wildcard(char *str);
int		get_base_path(char *word, char **base_path);
void	lst_insert_sort(t_list **list, t_list *new);
int		is_match(char *base_path, char *file_name);
int		get_directory(t_list **dir_list);

#endif
