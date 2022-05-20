/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:33:31 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 12:25:59 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

enum e_operator	operator_type(char *token)
{
	if (!ft_strcmp(token, "<"))
		return (infile);
	if (!ft_strcmp(token, ">"))
		return (outfile);
	if (!ft_strcmp(token, ">>"))
		return (appendout);
	if (!ft_strcmp(token, "<<"))
		return (here_doc);
	if (!ft_strcmp(token, "("))
		return (open_p);
	if (!ft_strcmp(token, ")"))
		return (close_p);
	if (!ft_strcmp(token, "&&"))
		return (and);
	if (!ft_strcmp(token, "||"))
		return (or);
	if (!ft_strcmp(token, "|"))
		return (conduit);
	return (nothing);
}

t_tree	*init_tree(char *token, char *prog_name)
{
	t_tree	*new_tree;

	new_tree = ft_calloc(1, sizeof(t_tree));
	if (!new_tree)
	{
		perror(prog_name);
		return (new_tree);
	}
	new_tree->type = operator_type(token);
	if (new_tree->type <= here_doc)
		new_tree->type = nothing;
	return (new_tree);
}

void	del_first_token(t_list **token_list)
{
	t_list	*to_free;

	to_free = *token_list;
	*token_list = (*token_list)->next;
	ft_lstdelone(to_free, &free);
}

void	free_tree(t_tree **tree)
{
	int	i;

	if (!*tree)
		return ;
	if ((*tree)->left)
		free_tree(&(*tree)->left);
	if ((*tree)->right)
		free_tree(&(*tree)->right);
	i = 0;
	while ((*tree)->pipe_children && (*tree)->pipe_children[i])
	{
		free_tree(&(*tree)->pipe_children[i]);
		i++;
	}
	free((*tree)->pipe_children);
	ft_lstclear(&(*tree)->arg, &free);
	ft_doc_lstclear(&(*tree)->here_doc);
	free((*tree)->infile);
	free((*tree)->outfile);
	free(*tree);
	tree = NULL;
}
