/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:30:46 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 12:30:54 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char	*prompt;
	char	*input;

	if (isatty(STDIN_FILENO))
		prompt = "$";
	else
		prompt = NULL;
	input = readline(prompt);
	return (input);
}
