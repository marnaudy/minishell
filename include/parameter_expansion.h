/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:03:43 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/06 11:34:34 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETER_EXPANSION_H
# define PARAMETER_EXPANSION_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdlib.h>
# include <unistd.h>

char	*replace_in_str(char *str, int start, int len, char *to_add);
int		parameter_len(char *str);
int		replace_parameter(char **str, int *idx, t_general_info *info);
int		bad_sub_message(char *parameter, char *prog_name, int print_braces);

#endif
