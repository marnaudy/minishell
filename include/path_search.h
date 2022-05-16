/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:11:17 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/16 17:10:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_SEARCH_H
# define PATH_SEARCH_H

# include "minishell.h"

char	**split_path(char const *s, char *prog_name);
int		no_path_search(char *arg0, char **path, char *prog_name);
int		search_path_array(char *arg0, char **path,
			char **path_arr, char *prog_name);

#endif
