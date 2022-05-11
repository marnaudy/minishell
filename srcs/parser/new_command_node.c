/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:13:53 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/11 14:14:37 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_token_to_arg(t_list **token_list, t_list **arg_list)
{
	t_list	*save;

	ft_lstadd_back(arg_list, *token_list);
	save = (*token_list)->next;
	(*token_list)->next = NULL;
	*token_list = save;
}

t_tree	*new_command_node(t_list **token_list, t_doc_list **doc_list,
			char *prog_name)
{
	t_tree			*new_tree;
	enum e_operator	op_type;

	op_type = operator_type((char *)(*token_list)->content);
	new_tree = init_tree((char *)(*token_list)->content, prog_name);
	if (!new_tree)
		return (NULL);
	while ((*token_list) && op_type <= here_doc)
	{
		if (op_type == nothing)
			add_token_to_arg(token_list, &new_tree->arg);
		if (op_type == infile)
			add_infile(new_tree, token_list);
		if (op_type == outfile || op_type == appendout)
			add_outfile(new_tree, token_list);
		if (op_type == here_doc)
			add_here_doc(new_tree, token_list, doc_list);
		if (*token_list)
			op_type = operator_type((char *)(*token_list)->content);
	}
	return (new_tree);
}
