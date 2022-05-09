/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:19:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/09 17:18:16 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_REMOVAL_H
# define QUOTE_REMOVAL_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdlib.h>

typedef struct s_int_list
{
	int					nb;
	struct s_int_list	*next;
}	t_int_list;

#endif
