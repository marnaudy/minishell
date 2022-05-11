/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:07 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/11 14:19:38 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_infile(t_tree *tree, t_list **token_list)
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

void	add_outfile(t_tree *tree, t_list **token_list)
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

void	add_here_doc(t_tree *tree, t_list **token_list, t_doc_list **doc_list)
{
	t_list	*save;

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
	save = *token_list;
	free((*token_list)->content);
	free((*token_list));
	*token_list = save->next;
	free(save->content);
	free(save);
}
