/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:32:30 by cboudrin          #+#    #+#             */
/*   Updated: 2022/05/24 15:00:07 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

char	*add_quotes(char *str, char *prog_name)
{
	char	*new;
	int		i;

	new = ft_calloc(ft_strlen(str) + 4, sizeof(char));
	if (!new)
	{
		perror(prog_name);
		return (NULL);
	}
	i = 0;
	while (str[i] != '=')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = str[i];
	new[i + 1] = '\"';
	ft_strlcat(new, &str[i + 1], ft_strlen(str) + 4);
	i = ft_strlen(new);
	new[i] = '\"';
	new[i + 1] = '\n';
	return (new);
}

int	display_export_env(t_general_info *info, int fd_out)
{
	char	**envp;
	char	*to_print;
	int		i;

	if (export_env(info, &envp))
		return (-1);
	i = 0;
	while (envp[i])
	{
		to_print = add_quotes(envp[i], info->prog_name);
		if (!to_print)
			return (-1);
		write(fd_out, "export ", 7);
		write(fd_out, to_print, ft_strlen(to_print));
		free(to_print);
		i++;
	}
	free_char_array_and_ret(envp, 0);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (0);
}
