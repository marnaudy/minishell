/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:19:56 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/02 16:54:56 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	exit_minishell(t_general_info *info)
{
	int	ret;

	ret = info->exit_code;
	free_general_info(info);
	exit(ret);
}

t_list	*get_token_list(t_general_info *info)
{
	char	*input;
	int		ret;
	t_list	*token_list;

	input = get_input(info->prog_name);
	if (!input)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_minishell(info);
	}
	ret = lexer(&token_list, input, info->prog_name);
	free(input);
	if (ret < 0)
	{
		info->exit_code = 1;
		exit_minishell(info);
	}
	if (ret)
	{
		info->exit_code = 2;
		return (NULL);
	}
	return (token_list);
}

int	check_token_list(t_list *token_list, t_general_info *info,
		t_redirect_list **doc_list)
{
	int	syntax_ret;

	syntax_ret = check_syntax(token_list, info->prog_name);
	if (syntax_ret < 0)
	{
		ft_lstclear(&token_list, &free);
		info->exit_code = 1;
		exit_minishell(info);
	}
	if (read_all_here_docs(token_list, info->prog_name,
			syntax_ret, doc_list) < 0)
	{
		ft_lstclear(&token_list, &free);
		info->exit_code = 1;
		exit_minishell(info);
	}
	if (syntax_ret)
	{
		ft_lstclear(&token_list, &free);
		ft_redirect_lstclear(doc_list);
		info->exit_code = 2;
		return (1);
	}
	return (0);
}

void	parse_and_exec(t_list *token_list, t_redirect_list *here_doc_list,
		t_general_info *info)
{
	if (parser(&info->root, &token_list, &here_doc_list,
			info->prog_name) < 0)
	{
		ft_lstclear(&token_list, &free);
		ft_redirect_lstclear(&here_doc_list);
		info->exit_code = 1;
		exit_minishell(info);
	}
	if (g_exit_code)
		info->exit_code = g_exit_code;
	g_exit_code = 0;
	if (set_signals_exec(info->prog_name) || exec_node(info->root, info, 0) < 0)
	{
		info->exit_code = 1;
		exit_minishell(info);
	}
	free_tree(&info->root);
}

int	main(int argc, char **argv, char **envp)
{
	t_list				*token_list;
	t_redirect_list		*here_doc_list;
	t_general_info		*info;

	(void)argc;
	info = init_info(argv[0], envp);
	if (!info)
		return (-1);
	g_exit_code = 0;
	info->exit_code = 0;
	while (1)
	{
		if (init_signals_read(info->prog_name))
		{
			info->exit_code = 1;
			exit_minishell(info);
		}
		token_list = get_token_list(info);
		if (!token_list || check_token_list(token_list, info, &here_doc_list))
			continue ;
		parse_and_exec(token_list, here_doc_list, info);
	}
	exit_minishell(info);
}
