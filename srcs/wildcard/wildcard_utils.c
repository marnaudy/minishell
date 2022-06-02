/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:25:37 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 19:28:34 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	free_lstclr_ret(void *to_free, t_list **list_free, int ret)
{
	free(to_free);
	ft_lstclear(list_free, &free);
	return (ret);
}
