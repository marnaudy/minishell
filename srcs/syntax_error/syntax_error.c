/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:16:19 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/04 12:03:36 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"

static int	update_parenthesis_count(t_list *token_list, int *nb_parentheses)
{
	if (((char *)token_list->content)[0] == '(')
		(*nb_parentheses)++;
	if (((char *)token_list->content)[0] == ')')
		(*nb_parentheses)--;
	if (*nb_parentheses < 0)
		return (1);
	if (token_list->next == NULL && *nb_parentheses != 0)
		return (1);
	return (0);
}

static int	print_error_message(t_list *token, char *prog_name)
{
	char	*to_print;
	char	*to_free;

	to_free = ft_strcat(prog_name, ": syntax error near unexpected token `");
	if (!to_free)
		return (-1);
	if (token)
		to_print = ft_strcat(to_free, ((char *) token->content));
	else
		to_print = ft_strcat(to_free, "newline");
	free(to_free);
	to_free = to_print;
	if (!to_print)
		return (-1);
	to_print = ft_strcat(to_print, "'\n");
	free(to_free);
	if (!to_print)
		return (-1);
	write(STDERR_FILENO, to_print, ft_strlen(to_print));
	free(to_print);
	return (0);
}

static int	error_printer_error_checker(t_list *token_list, char *prog_name, int next)
{
	int	ret;

	if (next)
		ret = print_error_message(token_list->next, prog_name);
	else
		ret = print_error_message(token_list, prog_name);
	if (ret)
	{
		perror(prog_name);
		return (-1);
	}
	return (1);
}

int	check_syntax(t_list *token_list, char *prog_name)
{
	int	nb_open_parentheses;

	nb_open_parentheses = 0;
	if (check_first_token(token_list->content))
		return (error_printer_error_checker(token_list, prog_name, 0));
	while (token_list)
	{
		if (update_parenthesis_count(token_list, &nb_open_parentheses))
			return (error_printer_error_checker(token_list, prog_name, 0));
		if (check_next_global(token_list))
			return (error_printer_error_checker(token_list, prog_name, 1));
		token_list = token_list->next;
	}
	return (0);
}

int	lexer(t_list **list, char *input, char *prog_name);

int main()
{
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
}
