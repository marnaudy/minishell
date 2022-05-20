/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:28:25 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/20 12:28:32 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_general_info	*free_general_info(t_general_info *info)
{
	if (info)
	{
		free_hash_table(info->table);
		free(info->prog_name);
		free_tree(&info->root);
		free(info);
	}
	return (NULL);
}

t_general_info	*init_info(char *arg0, char **envp)
{
	t_general_info	*info;
	int				i;

	info = ft_calloc(1, sizeof(t_general_info));
	if (!info)
	{
		perror(arg0);
		return (NULL);
	}
	info->table = init_env_table(envp);
	if (!info->table)
		return (free_general_info(info));
	i = ft_strlen(arg0) - 1;
	while (arg0[i] != '/' && i)
		i--;
	if (arg0[i] == '/')
		i++;
	info->prog_name = ft_strdup(&arg0[i]);
	if (!info->prog_name)
	{
		perror(arg0);
		free_general_info(info);
		return (NULL);
	}
	return (info);
}
