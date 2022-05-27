/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:07 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 19:57:08 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_file(t_tree *node, t_list **token_list, char *prog_name)
{
	t_redirect_list	*new_redirect;
	t_list			*to_free;

	new_redirect = ft_calloc(1, sizeof(t_redirect_list));
	if (!new_redirect)
	{
		perror(prog_name);
		return (-1);
	}
	new_redirect->type = operator_type((char *)(*token_list)->content);
	del_first_token(token_list);
	new_redirect->content = (char *)(*token_list)->content;
	to_free = *token_list;
	(*token_list) = (*token_list)->next;
	free(to_free);
	ft_redirect_lstadd_back(&node->redirects, new_redirect);
	return (0);
}

static void	add_here_doc(t_tree *node,
				t_list **token_list, t_redirect_list **doc_list)
{
	t_redirect_list	*to_add;

	to_add = *doc_list;
	*doc_list = (*doc_list)->next;
	to_add->next = NULL;
	ft_redirect_lstadd_back(&node->redirects, to_add);
	del_first_token(token_list);
	del_first_token(token_list);
}

int	add_redirection(t_tree *node, t_list **token_list,
			t_redirect_list **doc_list, char *prog_name)
{
	enum e_operator	op_type;

	op_type = operator_type((char *)(*token_list)->content);
	if (op_type == infile || op_type == outfile || op_type == appendout)
		return (add_file(node, token_list, prog_name));
	add_here_doc(node, token_list, doc_list);
	return (0);
}
