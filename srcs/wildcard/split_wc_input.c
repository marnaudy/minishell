/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:52:54 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 19:38:59 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	clear_wc_list_and_ret(t_wc_token **list, int ret,
		int print_err, char *prog_name)
{
	t_wc_token	*to_free;

	if (print_err)
		perror(prog_name);
	while (*list)
	{
		to_free = *list;
		*list = (*list)->next;
		free(to_free->text);
		free(to_free);
	}
	return (ret);
}

int	add_token_wc_list(t_wc_token **list, char *str, char *prog_name)
{
	t_wc_token	*new;
	t_wc_token	*iter;

	new = ft_calloc(1, sizeof(t_wc_token));
	if (!new)
		return (free_perror_and_ret(NULL, prog_name, 1, -1));
	if (str)
		new->text = str;
	else
		new->is_wc = 1;
	if (!*list)
	{
		*list = new;
		return (0);
	}
	iter = *list;
	while (iter->next)
		iter = iter->next;
	if (str || !iter->is_wc)
		iter->next = new;
	if (!str && iter->is_wc)
		free(new);
	return (0);
}

int	split_wc_input(t_wc_token **list, char *str, char *prog_name)
{
	int		i;
	int		j;
	char	*substr;

	i = 0;
	*list = NULL;
	while (str[i])
	{
		j = 0;
		if (str[i] != '*' || is_escaped(str, i))
		{
			while (str[i + j] && (str[i + j] != '*' || is_escaped(str, i + j)))
				j++;
			substr = ft_substr(str, i, j);
			if (!substr)
				return (clear_wc_list_and_ret(list, -1, 1, prog_name));
			if (add_token_wc_list(list, substr, prog_name))
				free_and_ret(str, NULL, clear_wc_list_and_ret(list, -1, 0, 0));
			j--;
		}
		if (str[i] == '*' && add_token_wc_list(list, NULL, prog_name))
			return (clear_wc_list_and_ret(list, -1, 0, NULL));
		i += j + 1;
	}
	return (0);
}

int	combine_wc_list_post_slash(t_wc_token *list, char *prog_name)
{
	t_wc_token	*to_free;
	char		*new_str;

	while (list)
	{
		if (!list->is_wc && ft_is_in_charset('/', list->text))
		{
			if (!list->next)
				return (0);
			if (list->next->is_wc)
				new_str = ft_strjoin(list->text, "*");
			else
				new_str = ft_strjoin(list->text, list->next->text);
			if (!new_str)
				return (free_perror_and_ret(NULL, prog_name, 1, -1));
			free(list->text);
			list->text = new_str;
			to_free = list->next;
			list->next = list->next->next;
			free(to_free);
		}
		else
			list = list->next;
	}
	return (0);
}

int	get_wc_list(t_wc_token **list, char *str, char *prog_name)
{
	t_wc_token	*iter;

	if (split_wc_input(list, str, prog_name))
		return (-1);
	iter = *list;
	while (iter)
	{
		if (!iter->is_wc && quote_removal(iter->text, prog_name))
			return (clear_wc_list_and_ret(list, -1, 0, prog_name));
		iter = iter->next;
	}
	if (combine_wc_list_post_slash(*list, prog_name))
		return (clear_wc_list_and_ret(list, -1, 0, prog_name));
	return (0);
}
