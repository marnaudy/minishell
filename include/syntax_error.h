/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:15:06 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/04 11:39:38 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERROR_H
# define SYNTAX_ERROR_H

# include "../libft/libft.h"
# include "lexer.h"

int	check_first_token(char *token);
int	check_next_global(t_list *token_list);

#endif
