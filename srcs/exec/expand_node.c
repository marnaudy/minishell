/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:44:10 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 14:26:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	free_perror_and_ret(void *to_free, char *prog_name,
		int print_error, int ret)
{
	if (print_error)
		perror(prog_name);
	free(to_free);
	return (ret);
}

static int	expand_parameters_node(t_tree *node, t_general_info *info)
{
	t_list	*list;

	list = node->arg;
	while (list)
	{
		if (replace_all_parameters((char **)&list->content, info, 0))
			return (-1);
		list = list->next;
	}
	if ((node->infile && replace_all_parameters(&node->infile, info, 0))
		|| (node->outfile && replace_all_parameters(&node->outfile, info, 0))
		|| (node->here_doc && !node->here_doc->is_quoted
			&& replace_all_parameters(&node->here_doc->content, info, 1)))
		return (-1);
	return (0);
}

static int	split_and_wildcard_str(char *str, char *prog_name)
{
	t_list	*new;

	if (!str)
		return (0);
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (free_perror_and_ret(NULL, prog_name, 1, -1));
	new->content = str;
	if (field_splitting(&new, prog_name))
	{
		ft_lstclear(&new->next, &free);
		return (free_and_ret((char *)new, NULL, -1));
	}
	if (expand_wildcards(new, prog_name))
	{
		ft_lstclear(&new->next, &free);
		return (free_and_ret((char *)new, NULL, -1));
	}
	if (new->next)
	{
		ft_lstclear(&new->next, &free);
		return (free_and_ret((char *)new, NULL, 1));
	}
	free(new);
	return (0);
}

static int	remove_quotes_node(t_tree *node, char *prog_name)
{
	t_list	*list;

	list = node->arg;
	while (list)
	{
		if (quote_removal((char *)list->content, prog_name))
			return (-1);
		list = list->next;
	}
	if ((node->infile && quote_removal(node->infile, prog_name))
		|| (node->outfile && quote_removal(node->outfile, prog_name))
		|| (node->here_doc && !node->here_doc->is_quoted
			&& quote_removal(node->here_doc->content, prog_name)))
		return (-1);
	return (0);
}

int	expand_node(t_tree *node, t_general_info *info)
{
	int	ret;

	if (expand_parameters_node(node, info))
		return (-1);
	if (field_splitting(&node->arg, info->prog_name))
		return (-1);
	if (expand_wildcards(node->arg, info->prog_name))
		return (-1);
	ret = split_and_wildcard_str(node->infile, info->prog_name);
	if (ret == 1)
		return (print_ambiguous_redirect(info->prog_name));
	if (ret)
		return (ret);
	ret = split_and_wildcard_str(node->outfile, info->prog_name);
	if (ret == 1)
		return (print_ambiguous_redirect(info->prog_name));
	if (ret)
		return (ret);
	if (remove_quotes_node(node, info->prog_name))
		return (-1);
	return (0);
}
