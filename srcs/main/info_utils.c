/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:28:25 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/24 15:41:24 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_general_info	*free_general_info(t_general_info *info)
{
	if (info)
	{
		free_env_list(&info->env);
		free(info->prog_name);
		free(info->cwd);
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
		return (perror(arg0), NULL);
	if (init_env_list(envp, info))
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
	info->cwd = getcwd(NULL, 0);
	if (!info->cwd)
		perror(arg0);
	return (info);
}
