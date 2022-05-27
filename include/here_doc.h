/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:48:40 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 19:34:09 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"
# include <readline/readline.h>
# include <unistd.h>

int	add_delimiter(t_list *token_list, char *prog_name,
		t_redirect_list **doc_list);
int	get_delimiters(t_list *token_list, char *prog_name,
		int nb_token, t_redirect_list **doc_list);

#endif
