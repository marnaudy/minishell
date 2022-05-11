/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:33:31 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/11 14:18:44 by marnaudy         ###   ########.fr       */
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
