/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:51:15 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/26 19:34:53 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static int	print_delimiter_error(char *delimiter, char *prog_name)
{
	char	*to_print;
	char	*to_free;

	to_free = ft_strcat(prog_name,
			": warning: here-document delimited by end-of-file (wanted `");
	if (!to_free)
		return (-1);
	to_print = ft_strcat(to_free, delimiter);
	free(to_free);
	to_free = to_print;
	if (!to_print)
		return (-1);
	to_print = ft_strcat(to_print, "\')\n");
	free(to_free);
	if (!to_print)
		return (-1);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	return (0);
}

static int	add_input(t_redirect_list *doc, char *input, char *prog_name)
{
	char	*to_free;

	to_free = doc->content;
	doc->content = ft_strcat(doc->content, input);
	if (!doc->content)
	{
		perror(prog_name);
		free(to_free);
		return (-1);
	}
	free(to_free);
	to_free = doc->content;
	doc->content = ft_strcat(doc->content, "\n");
	if (!doc->content)
	{
		perror(prog_name);
		free(to_free);
		return (-1);
	}
	free(to_free);
	return (0);
}

static int	read_here_doc(t_redirect_list *doc, char *prog_name)
{
	char	*input;
	char	*delimiter;
	char	*prompt;
	int		ret;

	delimiter = doc->content;
	doc->content = NULL;
	prompt = NULL;
	if (isatty(STDIN_FILENO))
		prompt = ">";
	input = readline(prompt);
	while (input && ft_strcmp(input, delimiter))
	{
		if (add_input(doc, input, prog_name))
			return (free_and_ret(input, delimiter, -1));
		free(input);
		input = readline(prompt);
	}
	ret = 0;
	if (!input)
		ret = print_delimiter_error(delimiter, prog_name);
	free(input);
	free(delimiter);
	return (ret);
}

// nb token is the index of the incorrect token (counting from 1)
// 0 means they're all ok
int	read_all_here_docs(t_list *token_list, char *prog_name,
	int nb_token, t_redirect_list **doc_list)
{
	t_redirect_list	*doc;
	int				fd_save;

	if (!isatty(STDIN_FILENO))
	{
		fd_save = disable_stdout(prog_name);
		if (fd_save == -1)
			return (-1);
	}
	*doc_list = NULL;
	if (get_delimiters(token_list, prog_name, nb_token, doc_list))
		return (-1);
	doc = *doc_list;
	while (doc)
	{
		if (read_here_doc(doc, prog_name))
			return (-1);
		doc = doc->next;
	}
	if (!isatty(STDIN_FILENO))
	{
		if (restore_stdout(fd_save, prog_name))
			return (-1);
	}
	return (0);
}
