/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:31:52 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/05 18:34:02 by marnaudy         ###   ########.fr       */
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
	t_hash_table	*table;
	char			*value;

	//Lexer and syntax test

	input = "echo ${\"prout\" && } $ & prout&&pouet && blqblq&bla ${{} \'blou\'\"blou\" \"${va\"r}\" \"}}}\"}\" bouet&&( cat&&&) <in $var$var ${var}${var} $prout \'$var\' \"$var\" \"$?var\"$va?r $$var? $DISPLAY \'$\'var $$$var $\"${var}\" echo $var ${var} $? ${\"var\"} \'$var\'";
	token_list = NULL;
	puts(input);
	ret = lexer(&token_list, input, "prout");
	printf("lexer return = %i\n", ret);
	ret = check_syntax(token_list, "prout");
	printf("check_syntax return = %i\n", ret);
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
	token_list = list_save;
	while (token_list)
	{
		ret = replace_all_parameters((char **) &token_list->content, 12, table, "prout");
		printf("return = %i, token = %s\n", ret, (char *)token_list->content);
		token_list = token_list->next;
	}
	ft_lstclear(&list_save, &free);
	free_hash_table(table);
}

// int	parameter_len(char *str);

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	printf("%i\n", parameter_len("$var\""));
// }
