/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:33:55 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 20:06:35 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_to_node(t_tree **working_node, t_tree *new_node)
{
	int	i;

	if (!*working_node)
	{
		*working_node = new_node;
		return ;
	}
	if ((*working_node)->type == conduit)
	{
		i = 0;
		while ((*working_node)->pipe_children[i])
			i++;
		(*working_node)->pipe_children[i] = new_node;
		return ;
	}
	if ((*working_node)->left)
		(*working_node)->right = new_node;
	else
		(*working_node)->left = new_node;
}

static int	free_error(t_tree **root,
				t_list **token_list, t_redirect_list **doc_list)
{
	free_tree(root);
	ft_lstclear(token_list, &free);
	ft_redirect_lstclear(doc_list);
	return (-1);
}

static t_tree	**get_working_node(t_tree **root)
{
	if (!(*root)->type || (*root)->type == open_p)
		return (root);
	return (&(*root)->right);
}

static int	add_node(t_tree **root, t_list **tk_list,
				t_redirect_list **doc_list, char *prog_name)
{
	t_tree			*new_node;
	int				op_type;

	op_type = operator_type((char *)(*tk_list)->content);
	if (op_type <= here_doc)
	{
		new_node = new_command_node(tk_list, doc_list, prog_name);
		if (!new_node)
			return (-1);
		add_to_node(root, new_node);
	}
	if (op_type == and || op_type == or)
		return (add_andor(root, tk_list, prog_name));
	if (op_type == conduit)
		return (add_pipe(get_working_node(root), tk_list, doc_list, prog_name));
	if (op_type == open_p)
		return (add_parentheses(root, tk_list, doc_list, prog_name));
	return (0);
}

int	parser(t_tree **root, t_list **tk_list,
		t_redirect_list **doc_list, char *prog_name)
{
	*root = NULL;
	while (*tk_list)
	{
		if (operator_type((char *)(*tk_list)->content) == close_p)
			return (0);
		if (add_node(root, tk_list, doc_list, prog_name))
			return (free_error(root, tk_list, doc_list));
	}
	return (0);
}
