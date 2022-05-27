/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:44:10 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 18:39:15 by marnaudy         ###   ########.fr       */
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

int	expand_args(t_tree *node, t_general_info *info)
{
	int	ret;

	ret = expand_parameters_in_list(node->arg, info);
	if (ret)
		return (ret);
	if (field_splitting(&node->arg, info->prog_name))
		return (-1);
	if (expand_wildcards(node->arg, info->prog_name))
		return (-1);
	if (remove_quotes_in_list(node->arg, info->prog_name))
		return (-1);
	return (0);
}
