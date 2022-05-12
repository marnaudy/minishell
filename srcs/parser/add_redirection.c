/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:07 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 15:04:35 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_infile(t_tree *tree, t_list **token_list)
{
	t_list	*save;

	save = (*token_list)->next;
	if (tree->here_doc)
	{
		free(tree->here_doc->content);
		free(tree->here_doc);
		tree->here_doc = NULL;
	}
	if (tree->infile)
	{
		free(tree->infile);
		tree->infile = NULL;
	}
	free((*token_list)->content);
	free((*token_list));
	tree->infile = (char *) save->content;
	(*token_list) = save->next;
	free(save);
}

static void	add_outfile(t_tree *tree, t_list **token_list)
{
	t_list	*save;

	save = (*token_list)->next;
	if (tree->outfile)
	{
		free(tree->outfile);
		tree->outfile = NULL;
	}
	tree->append_output
		= (operator_type((char *)(*token_list)->content) == appendout);
	free((*token_list)->content);
	free((*token_list));
	tree->outfile = (char *) save->content;
	(*token_list) = save->next;
	free(save);
}

static void	add_here_doc(t_tree *tree,
				t_list **token_list, t_doc_list **doc_list)
{
	if (tree->infile)
	{
		free(tree->infile);
		tree->infile = NULL;
	}
	if (tree->here_doc)
	{
		free(tree->here_doc->content);
		free(tree->here_doc);
		tree->here_doc = NULL;
	}
	tree->here_doc = *doc_list;
	*doc_list = (*doc_list)->next;
	tree->here_doc->next = NULL;
	del_first_token(token_list);
	del_first_token(token_list);
}

void	add_redirection(t_tree *node,
			t_list **token_list, t_doc_list **doc_list)
{
	enum e_operator	op_type;

	op_type = operator_type((char *)(*token_list)->content);
	if (op_type == infile)
		add_infile(node, token_list);
	if (op_type == outfile || op_type == appendout)
		add_outfile(node, token_list);
	if (op_type == here_doc)
		add_here_doc(node, token_list, doc_list);
}
