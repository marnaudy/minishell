/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:22:37 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 23:32:45 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static t_redirect_list	*ft_redirect_lstnew(char *content, int is_quoted,
							enum e_operator type)
{
	t_redirect_list	*new;

	new = malloc(sizeof(t_redirect_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->is_quoted = is_quoted;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_redirect_lstadd_back(t_redirect_list **alst, t_redirect_list *new)
{
	t_redirect_list	*lst;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	lst = *alst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

void	ft_redirect_lstclear(t_redirect_list **lst)
{
	t_redirect_list	*to_free;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free->content);
		free(to_free);
	}
}

static int	contains_quote(char *delimiter)
{
	return (ft_is_in_charset('\"', delimiter)
		|| ft_is_in_charset('\'', delimiter)
		|| ft_is_in_charset('\\', delimiter));
}

int	add_delimiter(t_list *token_list,
	char *prog_name, t_redirect_list **doc_list)
{
	t_redirect_list	*new_doc;
	char			*delim;

	if (!token_list->next || !token_list->next->content)
		return (-1);
	delim = ft_strdup((char *) token_list->next->content);
	if (!delim)
	{
		perror(prog_name);
		ft_redirect_lstclear(doc_list);
		return (-1);
	}
	new_doc = ft_redirect_lstnew(delim, contains_quote(delim), here_doc);
	if (!new_doc || quote_removal(delim, prog_name))
	{
		if (!new_doc)
			perror(prog_name);
		else
			free(new_doc);
		free(delim);
		ft_redirect_lstclear(doc_list);
		return (-1);
	}
	ft_redirect_lstadd_back(doc_list, new_doc);
	return (0);
}
