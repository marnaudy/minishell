/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:03:22 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 15:03:29 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"

int	check_first_token(char *token)
{
	return (!ft_strcmp(token, "&&")
		|| !ft_strcmp(token, "||")
		|| !ft_strcmp(token, "|"));
}
