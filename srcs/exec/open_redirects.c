/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:08:31 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/27 16:09:28 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_node.h"

int	open_file(t_redirect_list *redirect, char *prog_name,
		int *fd_in, int *fd_out)
{
	if (redirect->type == infile)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = open(redirect->content, O_RDONLY);
		if (*fd_in < 0)
			return (print_file_error(prog_name, redirect->content));
		return (0);
	}
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	if (redirect->type == appendout)
		*fd_out = open(redirect->content, O_WRONLY | O_APPEND | O_CREAT, 00644);
	else
		*fd_out = open(redirect->content, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	if (*fd_out < 0)
		return (print_file_error(prog_name, redirect->content));
	return (0);
}

int	open_here_doc(t_tree *node, t_general_info *info, int *fd_in)
{
	t_redirect_list	*last_here_doc;
	t_redirect_list	*redirect;

	last_here_doc = NULL;
	redirect = node->redirects;
	while (redirect)
	{
		if (redirect->type == here_doc)
			last_here_doc = redirect;
		redirect = redirect->next;
	}
	if (!last_here_doc)
		return (0);
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = launch_here_doc_writer(last_here_doc->content, info);
	if (*fd_in < 0)
		return (-1);
	return (0);
}

int	open_redirects(t_tree *node, t_general_info *info, int *fd_in, int *fd_out)
{
	t_redirect_list	*redir_list;
	int				ret;

	*fd_in = STDIN_FILENO;
	*fd_out = STDOUT_FILENO;
	redir_list = node->redirects;
	while (redir_list)
	{
		ret = expand_redirect(redir_list, info);
		if (ret)
			return (ret);
		if (redir_list->type != here_doc
			&& open_file(redir_list, info->prog_name, fd_in, fd_out))
			return (-1);
		redir_list = redir_list->next;
	}
	return (open_here_doc(node, info, fd_in));
}

int	redirect(t_tree *node, t_general_info *info)
{
	int	fd_in;
	int	fd_out;
	int	ret;

	ret = open_redirects(node, info, &fd_in, &fd_out);
	if (ret)
		return (ret);
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (free_perror_and_ret(NULL, info->prog_name, 1, -1));
		close(fd_out);
	}
	return (0);
}
