/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:02:58 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 15:23:51 by marnaudy         ###   ########.fr       */
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

static int	expand_filename(char **filename, t_general_info *info)
{
	int		ret;
	t_list	*tmp;

	tmp = ft_calloc(1, sizeof(t_list));
	if (!tmp)
		return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
	ret = replace_all_parameters(filename, info, 0);
	if (ret)
		return (ret);
	tmp->content = *filename;
	if (field_splitting(&tmp, info->prog_name)
		|| expand_wildcards(tmp, info->prog_name))
		return (free_lstclear_ret(&tmp->next, tmp, -1));
	if (!tmp || tmp->next)
	{
		if (tmp)
			*filename = tmp->content;
		if (tmp)
			ft_lstclear(&tmp->next, &free);
		else
			*filename = NULL;
		return (free_and_ret((char *)tmp, NULL, 1));
	}
	free(tmp);
	return (0);
}

int	expand_redirect(t_redirect_list *redirect, t_general_info *info)
{
	int		ret;
	char	*token_save;

	if (redirect->type == here_doc)
	{
		if (redirect->is_quoted)
			return (0);
		return (replace_all_parameters(&redirect->content, info, 1));
	}
	token_save = ft_strdup(redirect->content);
	if (!token_save)
	{
		perror(info->prog_name);
		return (-1);
	}
	ret = expand_filename(&redirect->content, info);
	if (ret == 1)
		print_ambiguous_redirect(token_save, info->prog_name);
	free(token_save);
	return (ret);
}
