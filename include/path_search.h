/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:11:17 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/25 12:01:14 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_SEARCH_H
# define PATH_SEARCH_H

# include "minishell.h"

char	**split_path(char const *s, char *prog_name);
int		check_file(char *filename, char *prog_name, int path_search);
int		no_path_search(char *arg0, char **path, char *prog_name);
int		search_path_array(char *arg0, char **path,
			char **path_arr, char *prog_name);

#endif
