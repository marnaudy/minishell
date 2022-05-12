/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:38:26 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 14:45:11 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"

static int	check_redirection_next(t_list *token_list)
{
	return (token_list->next == NULL
		|| is_operator(((char *) token_list->next->content),
			ft_strlen(((char *) token_list->next->content))));
}

static int	check_parenthesis_next(t_list *token_list)
{
	enum e_operator	op_type;
	int				i;

	if (token_list->next == NULL)
		return (!ft_strcmp((char *) token_list->content, "("));
	if (((char *)token_list->content)[0] == '(')
		return (check_first_token((char *) token_list->next->content)
			|| ((char*) token_list->next->content)[0] == ')');
	token_list = token_list->next;
	op_type = operator_type((char *)token_list->content);
	i = 1;
	while (op_type >= infile && op_type <= here_doc)
	{
		if (!token_list->next || !token_list->next->next)
			return (0);
		token_list = token_list->next->next;
		i += 2;
		op_type = operator_type((char *)token_list->content);
	}
	if (op_type == nothing || op_type == open_p)
		return (i);
	return (0);
}

static int	check_and_or_next(t_list	*token_list)
{
	if (token_list->next == NULL)
		return (1);
	return (check_first_token((char *) token_list->next->content)
		|| !ft_strcmp((char *) token_list->next->content, ")"));
}

static int	check_pipe_next(t_list	*token_list)
{
	if (token_list->next == NULL)
		return (1);
	return (check_first_token((char *) token_list->next->content)
		|| !ft_strcmp((char *) token_list->next->content, ")"));
}

int	check_next_global(t_list *token_list)
{
	if (!ft_strcmp((char *) token_list->content, "<")
		|| !ft_strcmp((char *) token_list->content, "<<")
		|| !ft_strcmp((char *) token_list->content, ">")
		|| !ft_strcmp((char *) token_list->content, ">>"))
		return (check_redirection_next(token_list));
	if (!ft_strcmp((char *) token_list->content, ")")
		|| !ft_strcmp((char *) token_list->content, "("))
		return (check_parenthesis_next(token_list));
	if (!ft_strcmp((char *) token_list->content, "||")
		|| !ft_strcmp((char *) token_list->content, "&&"))
		return (check_and_or_next(token_list));
	if (!ft_strcmp((char *) token_list->content, "|"))
		return (check_pipe_next(token_list));
	return (token_list->next && ((char *) token_list->next->content)[0] == '(');
}
