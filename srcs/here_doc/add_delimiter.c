/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:22:37 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/10 15:02:10 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static t_doc_list	*ft_doc_lstnew(char *content, int is_quoted)
{
	t_doc_list	*new;

	new = malloc(sizeof(t_doc_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->is_quoted = is_quoted;
	new->next = NULL;
	return (new);
}

static void	ft_doc_lstadd_back(t_doc_list **alst, t_doc_list *new)
{
	t_doc_list	*lst;

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

void	ft_doc_lstclear(t_doc_list **lst)
{
	t_doc_list	*to_free;

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
	char *prog_name, t_doc_list **doc_list)
{
	t_doc_list	*new_doc;
	char		*delimiter;

	delimiter = ft_strdup((char *) token_list->next->content);
	if (!delimiter)
	{
		perror(prog_name);
		ft_doc_lstclear(doc_list);
		return (-1);
	}
	new_doc = ft_doc_lstnew(delimiter, contains_quote(delimiter));
	if (!new_doc || quote_removal(delimiter, prog_name))
	{
		if (!new_doc)
			perror(prog_name);
		else
			free(new_doc);
		free(delimiter);
		ft_doc_lstclear(doc_list);
		return (-1);
	}
	ft_doc_lstadd_back(doc_list, new_doc);
	return (0);
}
