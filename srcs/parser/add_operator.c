/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:23:45 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 20:06:13 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_andor(t_tree **root, t_list **token_list, char *prog_name)
{
	t_tree	*new_node;

	new_node = init_tree((char *)(*token_list)->content, prog_name);
	if (!new_node)
		return (-1);
	del_first_token(token_list);
	new_node->left = *root;
	*root = new_node;
	return (0);
}

static int	count_pipes(t_list *token_list)
{
	int				count;
	enum e_operator	op_type;

	count = 0;
	op_type = operator_type((char *)token_list->content);
	while (token_list && (op_type <= here_doc || op_type == conduit))
	{
		if (op_type == conduit)
			count++;
		token_list = token_list->next;
		if (token_list)
			op_type = operator_type((char *)token_list->content);
	}
	return (count);
}

static int	add_pipe_children(t_tree **pipe_node, t_list **token_list,
				t_redirect_list **doc_list, char *prog_name)
{
	int		i;
	int		nb_children;

	nb_children = count_pipes(*token_list) + 1;
	i = 1;
	while (i < nb_children)
	{
		del_first_token(token_list);
		if (operator_type((char *)(*token_list)->content) == open_p)
		{
			if (add_parentheses(pipe_node, token_list, doc_list, prog_name))
				return (-1);
		}
		else
		{
			(*pipe_node)->pipe_children[i]
				= new_command_node(token_list, doc_list, prog_name);
			if (!(*pipe_node)->pipe_children[i])
				return (-1);
		}
		i++;
	}
	(*pipe_node)->pipe_children[i] = NULL;
	return (0);
}

int	add_pipe(t_tree **working_node, t_list **token_list,
		t_redirect_list **doc_list, char *prog_name)
{
	t_tree	*new_node;

	new_node = init_tree((char *)(*token_list)->content, prog_name);
	if (!new_node)
		return (-1);
	new_node->pipe_children
		= ft_calloc(sizeof(t_tree *), count_pipes(*token_list) + 2);
	if (!new_node->pipe_children)
	{
		free(new_node);
		return (-1);
	}
	new_node->pipe_children[0] = *working_node;
	if (add_pipe_children(&new_node, token_list, doc_list, prog_name))
	{
		free_tree(&new_node);
		*working_node = NULL;
		return (-1);
	}
	*working_node = new_node;
	return (0);
}
