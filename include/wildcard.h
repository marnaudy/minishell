/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:14 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/13 16:38:42 by cboudrin         ###   ########.fr       */
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

int		has_wildcard(char *str);
int		get_base_path(char *word, char **base_path);
void	lst_insert_sort(t_list **list, t_list *new);
int		is_match(char *base_path, char *file_name);

#endif






