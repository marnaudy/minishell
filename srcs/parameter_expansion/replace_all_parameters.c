/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_all_parameters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:36:29 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/01 16:52:43 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

int	replace_all_parameters(char **str, t_general_info *info, int ignore_quotes)
{
	int	idx;
	int	is_quoted;
	int	ret;

	idx = 0;
	is_quoted = 0;
	while (*str && (*str)[idx])
	{
		if ((*str)[idx] == '\"' && !is_escaped(*str, idx))
			is_quoted = !is_quoted;
		if (!ignore_quotes && !is_quoted
			&& skip_simple_quote(*str, 0, &idx) == 0)
			continue ;
		ret = replace_parameter(str, &idx, info, ignore_quotes);
		if (ret)
			return (ret);
		idx++;
	}
	return (0);
}
