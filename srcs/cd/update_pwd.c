/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:38:00 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/31 13:38:09 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	update_pwd(t_general_info *info)
{
	char	*old_pwd;
	char	*key;
	char	*new_pwd;

	old_pwd = fetch_value(info->env, "PWD");
	if (old_pwd)
	{
		old_pwd = ft_strdup(old_pwd);
		if (!old_pwd)
			return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
		key = ft_strdup("OLDPWD");
		if (!key)
			return (free_perror_and_ret(old_pwd, info->prog_name, 1, -1));
		if (add_to_env(info, key, old_pwd, 1))
			return (free_and_ret(old_pwd, key, -1));
	}
	key = ft_strdup("PWD");
	if (!key)
		return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
	new_pwd = ft_strdup(info->cwd);
	if (!new_pwd)
		return (free_perror_and_ret(key, info->prog_name, 1, -1));
	if (add_to_env(info, key, new_pwd, 1))
		return (free_and_ret(NULL, key, -1));
	return (0);
}
