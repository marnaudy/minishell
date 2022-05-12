/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:31:52 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 15:21:53 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_list			*list_save;
	t_list			*token_list;
	char			*input;
	int				ret;
	int				syntax_ret;
	t_hash_table	*table;
	char			*value;
	t_general_info	info;
	unsigned int	i;
	t_doc_list		*doc_list;
	t_doc_list		*doc_list_save;
	t_tree			*tree;

	//Lexer and syntax test

	// input = "echo ${\"pro\\\"ut\" && } $& $var<<eof \\\'prout&&pouet && blqblq&bla ${{\\}baobab} \'blou\'\"blou\" \"${va\"r}\" \"}}}\"}\" bouet&&( cat&&&) || in $var$var ${var}${var} $prout \'$var\' \"$var\" \"$?var\"$va?r $$var? $DISPLAY \'$\'var $$$var $\"${var}\" echo $var ${var} $? ${\"var\"} |  \'$var\' \"\\\\\\\" \\\' ${\\\" \\\\ \\} \'\\\' \\a\' }\" p{var}";
	// input = "echo a < in >out>out2 && (echo b>>out << eof) | echo a | echo b <<out  || echo c< in < in2 | cat -e || (ls || ls) < in";
	input = "(echo a && echo b) | cat";
	i = 0;
	while (i < ft_strlen(input))
	{
		//printf("%c is escaped : %i\n", input[i], is_escaped(input, i));
		i++;
	}
	token_list = NULL;
	puts(input);
	ret = lexer(&token_list, input, "prout");
	printf("lexer return = %i\n", ret);
	syntax_ret = check_syntax(token_list, "prout");
	printf("check_syntax return = %i\n", syntax_ret);
	list_save = token_list;
	while (token_list)
	{
		printf("_%s_\n", (char *) token_list->content);
		token_list = token_list->next;
	}

	//ENV test
	
	(void) argv;
	(void) argc;
	argv[argc - 1] = NULL;
	table = init_env_table(envp);
	input = get_next_line(0);
	while (input)
	{
		input[ft_strlen(input) - 1] = 0;
		value = fetch_value(table, input);
		if (value)
			printf("%s\n", value);
		else
			printf("%p\n", value);
		input = get_next_line(0);
	}

	// Parameter expansion
	info.exit_code = 12;
	info.prog_name = "prout";
	info.table = table;
	token_list = list_save;
	while (token_list)
	{
		ret = replace_all_parameters((char **) &token_list->content, &info, 0);
		printf("return = %i, token = %s\n", ret, (char *)token_list->content);
		token_list = token_list->next;
	}
	input = ft_strdup("\'${blaploufproutbla\n");
	ret = replace_all_parameters(&input, &info, 1);
	printf("return = %i, token = %s\n", ret, input);
	free(input);

	// Quote removal
	printf("----Quote removal-----------------------------------------------------\n");
	token_list = list_save;
	while (token_list)
	{
		ret = quote_removal(((char *)token_list->content), "prout");
		printf("return = %i, token = %s\n", ret, (char *)token_list->content);
		token_list = token_list->next;
	}

	// Read heredocs
	printf("----Here docs-----------------------------------------------------\n");
	token_list = list_save;
	ret = read_all_here_docs(token_list, "prout", syntax_ret, &doc_list);
	doc_list_save = doc_list;
	printf("return = %i\n", ret);
	while (doc_list)
	{
		printf("heredoc = _%s_ is_quote = %i\n", doc_list->content, doc_list->is_quoted);
		doc_list = doc_list->next;
	}
	if (syntax_ret)
	{
		ft_lstclear(&list_save, &free);
		ft_doc_lstclear(&doc_list_save);
		free_hash_table(table);
		return (0);
	}
	// Parse token list
	printf("----Parsing-----------------------------------------------------\n");
	token_list = list_save;
	doc_list = doc_list_save;
	ret = parser(&tree, &token_list, &doc_list, "prout");
	printf("return = %i, tree = %p\n", ret, tree);
	print_tree(tree);

	free_tree(&tree);
	free_hash_table(table);
}
