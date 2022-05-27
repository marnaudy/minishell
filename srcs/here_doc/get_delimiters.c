/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:01:09 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 19:33:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	get_delimiters(t_list *token_list, char *prog_name,
	int nb_token, t_redirect_list **doc_list)
{
	int			i;

	*doc_list = NULL;
	i = 1;
	while ((i < nb_token || nb_token == 0) && token_list)
	{
		if (!ft_strcmp(((char *)token_list->content), "<<"))
		{
			if (add_delimiter(token_list, prog_name, doc_list))
				return (-1);
		}
		token_list = token_list->next;
		i++;
	}
	return (0);
}
