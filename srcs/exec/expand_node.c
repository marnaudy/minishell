/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:44:10 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/25 15:29:12 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

static int	expand_parameters_in_list(t_list *list, t_general_info *info)
{
	int	ret;

	while (list)
	{
		ret = replace_all_parameters((char **)&list->content, info, 0);
		if (ret)
			return (ret);
		list = list->next;
	}
	return (0);
}

static int	expand_parameters_node(t_tree *node, t_general_info *info)
{
	t_file_list	*file_list;
	int			ret;

	ret = expand_parameters_in_list(node->arg, info);
	if (ret)
		return (ret);
	ret = expand_parameters_in_list(node->infile, info);
	if (ret)
		return (ret);
	file_list = node->outfile;
	while (file_list)
	{
		ret = replace_all_parameters(&file_list->name, info, 0);
		if (ret)
			return (ret);
		file_list = file_list->next;
	}
	if (node->here_doc && !node->here_doc->is_quoted)
		return (replace_all_parameters(&node->here_doc->content, info, 1));
	return (0);
}

static int	remove_quotes_in_list(t_list *list, char *prog_name)
{
	while (list)
	{
		if (quote_removal((char *)list->content, prog_name))
			return (-1);
		list = list->next;
	}
	return (0);
}

static int	remove_quotes_node(t_tree *node, char *prog_name)
{
	t_file_list	*file_list;

	if (remove_quotes_in_list(node->arg, prog_name))
		return (-1);
	if (remove_quotes_in_list(node->infile, prog_name))
		return (-1);
	file_list = node->outfile;
	while (file_list)
	{
		if (quote_removal(file_list->name, prog_name))
			return (-1);
		file_list = file_list->next;
	}
	if ((node->here_doc && !node->here_doc->is_quoted
			&& quote_removal(node->here_doc->content, prog_name)))
		return (-1);
	return (0);
}

int	expand_node(t_tree *node, t_general_info *info)
{
	int	ret;

	ret = expand_parameters_node(node, info);
	if (ret)
		return (ret);
	if (field_splitting(&node->arg, info->prog_name))
		return (-1);
	if (expand_wildcards(node->arg, info->prog_name))
		return (-1);
	ret = split_and_wildcard_file(node, info->prog_name);
	if (ret)
		return (ret);
	if (remove_quotes_node(node, info->prog_name))
		return (-1);
	return (0);
}
