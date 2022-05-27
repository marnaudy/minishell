/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parentheses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:41:41 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 19:59:28 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_parentheses(t_tree **root, t_list **token_list,
		t_redirect_list **doc_list, char *prog_name)
{
	enum e_operator	op_type;
	t_tree			*new_node;

	new_node = init_tree((char *)(*token_list)->content, prog_name);
	if (!new_node)
		return (-1);
	del_first_token(token_list);
	add_to_node(root, new_node);
	if (parser(&new_node->left, token_list, doc_list, prog_name))
		return (-1);
	del_first_token(token_list);
	if (!(*token_list))
		return (0);
	op_type = operator_type((char *)(*token_list)->content);
	while ((*token_list) && op_type <= here_doc)
	{
		if (add_redirection(new_node, token_list, doc_list, prog_name))
			return (-1);
		if (*token_list)
			op_type = operator_type((char *)(*token_list)->content);
	}
	return (0);
}
