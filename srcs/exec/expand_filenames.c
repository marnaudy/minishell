/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filenames.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:02:58 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/23 16:03:55 by marnaudy         ###   ########.fr       */
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

static int	free_lstclear_ret(t_list **list, void *to_free, int ret)
{
	ft_lstclear(list, &free);
	free(to_free);
	return (ret);
}

static int	split_and_wildcard_str(char **str, char *prog_name)
{
	t_list	*new;

	if (!str)
		return (0);
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (free_perror_and_ret(NULL, prog_name, 1, -1));
	new->content = *str;
	if (field_splitting(&new, prog_name))
		return (free_lstclear_ret(&new->next, new, -1));
	if (expand_wildcards(new, prog_name))
		return (free_lstclear_ret(&new->next, new, -1));
	if (!new || new->next)
	{
		if (new)
			ft_lstclear(&new->next, &free);
		else
			*str = NULL;
		return (free_and_ret((char *)new, NULL, 1));
	}
	free(new);
	return (0);
}

int	split_and_wildcard_file(t_tree *node, char *prog_name)
{
	int			ret;
	t_list		*iter_in;
	t_file_list	*iter_out;

	iter_in = node->infile;
	while (iter_in)
	{
		ret = split_and_wildcard_str((char **) &iter_in->content, prog_name);
		if (ret == 1)
			return (print_ambiguous_redirect(prog_name));
		if (ret)
			return (ret);
		iter_in = iter_in->next;
	}
	iter_out = node->outfile;
	while (iter_out)
	{
		ret = split_and_wildcard_str(&iter_out->name, prog_name);
		if (ret == 1)
			return (print_ambiguous_redirect(prog_name));
		if (ret)
			return (ret);
		iter_out = iter_out->next;
	}
	return (0);
}
