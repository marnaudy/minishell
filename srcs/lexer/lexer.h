/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:11:48 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/02 15:21:56 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include "../../libft/libft.h"

int	is_blank(char c);
int	is_operator(char *str, int len);
int	can_add_to_token(char *token, int token_len);

#endif
