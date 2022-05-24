/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:11:48 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/24 16:58:45 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "minishell.h"

int	is_operator(char *str, int len);
int	can_add_to_token(char *token, int token_len);
int	skip_quote(char *input, int idx, int *token_len);
int	skip_parameter(char *input, int idx, int *token_len);

#endif
