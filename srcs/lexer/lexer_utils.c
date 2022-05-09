/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:01:45 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 12:03:16 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_blank(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\f'
		|| c == '\r'
		|| c == '\v'
	);
}

static int	is_operator_char(char c)
{
	return (c == '&'
		|| c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '('
		|| c == ')'
	);
}

int	is_operator(char *str, int len)
{
	if (len > 2)
		return (0);
	if (!is_operator_char(str[0]))
		return (0);
	if (len == 2 && (str[0] == '(' || str[0] == ')'))
		return (0);
	if (len == 2)
		return (str[0] == str[1]);
	if (str[0] == '&' && str[1] != '&')
		return (0);
	return (1);
}

int	can_add_to_token(char *token, int token_len)
{
	return (token[token_len] != 0
		&& !is_blank(token[token_len])
		&& ((is_operator(&token[0], token_len)
				&& is_operator(&token[0], token_len + 1))
			|| (!is_operator(&token[0], token_len)
				&& !(is_operator(&token[token_len], 1)
					&& !is_escaped(token, token_len)))));
}
