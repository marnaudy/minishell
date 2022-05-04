#include "minishell.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	//Lexer and syntax test
	t_list	*token_list;
	char *input = "echo ${\"prout\" && } $ & prout&&pouet && blqblq&bla ${{} \'blou\'\"blou\" \"${va\"r}\" \"}}}\"}\" bouet&&( cat&&) <";

	token_list = NULL;
	puts(input);
	int ret = lexer(&token_list, input, "prout");
	printf("lexer return = %i\n", ret);
	ret = check_syntax(token_list, "prout");
	printf("check_syntax return = %i\n", ret);
	while (token_list)
	{
		printf("_%s_\n", (char *) token_list->content);
		token_list = token_list->next;
	}
	//ENV test
	t_hash_table *table;
	char		*value;

	(void) envp;
	argv[argc - 1] = NULL;
	table = init_env_table(argv);
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
	free_hash_table(table);
}
