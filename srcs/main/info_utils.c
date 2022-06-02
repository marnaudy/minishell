/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:28:25 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 16:38:42 by marnaudy         ###   ########.fr       */
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

void	exit_init(t_general_info *info, int print_error)
{
	if (print_error && info)
		perror(info->prog_name);
	free_general_info(info);
	exit(-1);
}

void	init_pwd(t_general_info *info)
{
	char	*pwd;
	char	*cwd;

	if (!info->cwd)
		return ;
	pwd = ft_strdup("PWD");
	if (!pwd)
		exit_init(info, 1);
	remove_value(&info->env, "PWD");
	cwd = ft_strdup(info->cwd);
	if (!cwd)
		exit_init(info, 1);
	if (add_to_env(info, pwd, cwd, 1))
		exit_init(info, 0);
	return ;
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
		ft_putstr_fd("Error retrieving current directory\n", STDERR_FILENO);
	init_pwd(info);
	return (info);
}
