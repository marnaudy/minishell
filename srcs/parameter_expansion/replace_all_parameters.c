/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_all_parameters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:36:29 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/05 18:36:49 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameter_expansion.h"

int	replace_all_parameters(char **str, int exit_code,
		t_hash_table *table, char *prog_name)
{
	int	idx;
	int	is_quoted;
	int	ret;

	idx = 0;
	is_quoted = 0;
	while ((*str)[idx])
	{
		if ((*str)[idx] == '\"')
			is_quoted = !is_quoted;
		if (!is_quoted && skip_simple_quote(*str, 0, &idx) == 0)
			continue ;
		ret = replace_parameter(str, exit_code, &idx, table, prog_name);
		if (ret)
			return (ret);
		idx++;
	}
	return (0);
}
