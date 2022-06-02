/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:32:30 by cboudrin          #+#    #+#             */
/*   Updated: 2022/06/02 15:44:46 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	env_size(t_env_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->export)
			i++;
		env = env->next;
	}
	return (i);
}

char	*key_val_pair_to_str(char *key, char *value, char *prog_name)
{
	int		len;
	char	*str;

	len = ft_strlen(key) + ft_strlen(value) + ft_strlen("export =\"\"\n") + 1;
	str = ft_calloc(len, sizeof(char));
	if (!str)
	{
		perror(prog_name);
		return (NULL);
	}
	ft_strlcpy(str, "export ", len);
	ft_strlcat(str, key, len);
	if (value)
	{
		ft_strlcat(str, "=\"", len);
		ft_strlcat(str, value, len);
		ft_strlcat(str, "\"\n", len);
	}
	else
		ft_strlcat(str, "\n", len);
	return (str);
}

t_env_list	*get_env_arr(t_env_list *env_list, char *prog_name, int *size)
{
	int			i;
	t_env_list	*arr;

	*size = env_size(env_list);
	arr = ft_calloc(*size, sizeof(t_env_list));
	if (!arr)
	{
		perror(prog_name);
		return (NULL);
	}
	i = 0;
	while (env_list)
	{
		if (env_list->export)
		{
			arr[i].key = env_list->key;
			arr[i].value = env_list->value;
			i++;
		}
		env_list = env_list->next;
	}
	return (arr);
}

int	print_env_arr(t_env_list *env_arr, int size, int fd_out, char *prog_name)
{
	char	*to_print;
	int		i;

	i = 0;
	while (i < size)
	{
		to_print
			= key_val_pair_to_str(env_arr[i].key, env_arr[i].value, prog_name);
		if (!to_print)
			return (-1);
		ft_putstr_fd(to_print, fd_out);
		free(to_print);
		i++;
	}
	return (0);
}

int	display_export_env(t_general_info *info, int fd_out)
{
	t_env_list	*env_arr;
	int			size;

	env_arr = get_env_arr(info->env, info->prog_name, &size);
	if (!env_arr)
		return (-1);
	sort_env_arr(env_arr, size);
	if (print_env_arr(env_arr, size, fd_out, info->prog_name))
	{
		free(env_arr);
		return (-1);
	}
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	free(env_arr);
	return (0);
}
