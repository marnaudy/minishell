/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:07 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 14:21:22 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_infile(t_tree *tree, t_list **token_list, char *prog_name)
{
	t_list	*save;
	t_list	*new;

	save = (*token_list)->next;
	if (tree->here_doc)
	{
		free(tree->here_doc->content);
		free(tree->here_doc);
		tree->here_doc = NULL;
	}
	free((*token_list)->content);
	free((*token_list));
	new = ft_lstnew(save->content);
	if (!new)
	{
		perror(prog_name);
		return (-1);
	}
	ft_lstadd_back(&tree->infile, new);
	(*token_list) = save->next;
	free(save);
	return (0);
}

static int	add_outfile(t_tree *tree, t_list **token_list, char *prog_name)
{
	t_list		*save;
	t_file_list	*new;
	t_file_list	*iter;

	save = (*token_list)->next;
	new = ft_calloc(1, sizeof(t_file_list));
	if (!new)
		return (free_perror_and_ret(NULL, prog_name, 1, -1));
	new->append = (operator_type((char *)(*token_list)->content) == appendout);
	free((*token_list)->content);
	free((*token_list));
	new->name = (char *) save->content;
	(*token_list) = save->next;
	free(save);
	if (!tree->outfile)
	{
		tree->outfile = new;
		return (0);
	}
	iter = tree->outfile;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
	return (0);
}

static void	add_here_doc(t_tree *tree,
				t_list **token_list, t_doc_list **doc_list)
{
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
			t_list **token_list, t_doc_list **doc_list, char *prog_name)
{
	enum e_operator	op_type;

	op_type = operator_type((char *)(*token_list)->content);
	if (op_type == infile)
		add_infile(node, token_list, prog_name);
	if (op_type == outfile || op_type == appendout)
		add_outfile(node, token_list, prog_name);
	if (op_type == here_doc)
		add_here_doc(node, token_list, doc_list);
}
