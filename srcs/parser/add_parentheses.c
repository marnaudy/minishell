/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parentheses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:41:41 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 12:41:59 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_parentheses(t_tree **root, t_list **token_list, t_doc_list **doc_list,
		char *prog_name)
{
	t_tree	*new_node;

	new_node = init_tree((char *)(*token_list)->content, prog_name);
	if (!new_node)
		return (-1);
	del_first_token(token_list);
	add_to_node(root, new_node);
	if (parser(&new_node->left, token_list, doc_list, prog_name))
		return (-1);
	del_first_token(token_list);
	return (0);
}
