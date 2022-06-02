# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 17:15:05 by marnaudy          #+#    #+#              #
#    Updated: 2022/06/02 20:52:16 by marnaudy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

LIBFT	=	libft/libft.a

SRCS	=	srcs/lexer/lexer_parameter.c \
			srcs/lexer/is_escaped.c \
			srcs/lexer/lexer_quote.c \
			srcs/lexer/lexer_utils.c \
			srcs/lexer/lexer.c \
			srcs/syntax_error/check_first_token.c \
			srcs/syntax_error/check_token.c \
			srcs/syntax_error/syntax_error.c \
			srcs/environment/environment.c \
			srcs/environment/free_environment.c \
			srcs/environment/init_environment.c \
			srcs/environment/export_environment.c \
			srcs/parameter_expansion/replace_in_str.c \
			srcs/parameter_expansion/parameter_len.c \
			srcs/parameter_expansion/bad_substitution.c \
			srcs/parameter_expansion/add_backslash.c \
			srcs/parameter_expansion/replace_parameter.c \
			srcs/parameter_expansion/replace_all_parameters.c \
			srcs/quote_removal/quote_removal.c \
			srcs/here_doc/add_delimiter.c \
			srcs/here_doc/get_delimiters.c \
			srcs/here_doc/read_here_doc.c \
			srcs/here_doc/write_here_doc.c \
			srcs/parser/parser_utils.c \
			srcs/parser/add_redirection.c \
			srcs/parser/new_command_node.c \
			srcs/parser/add_operator.c \
			srcs/parser/add_parentheses.c \
			srcs/parser/parser.c \
			srcs/field_splitting/field_splitting.c \
			srcs/wildcard/wildcard_utils.c \
			srcs/wildcard/has_wildcard.c \
			srcs/wildcard/lst_insert_sort.c \
			srcs/wildcard/get_directory.c \
			srcs/wildcard/split_wc_input.c \
			srcs/wildcard/is_match.c \
			srcs/wildcard/wildcard.c \
			srcs/path_search/split_path.c \
			srcs/path_search/path_search_utils.c \
			srcs/path_search/check_file.c \
			srcs/path_search/path_search.c \
			srcs/exec/write_file_error.c \
			srcs/exec/open_redirects.c \
			srcs/exec/ambiguous_redirect.c \
			srcs/exec/expand_redirect.c \
			srcs/exec/expand_args.c \
			srcs/exec/wait_child.c \
			srcs/exec/exec_command_node.c \
			srcs/exec/launch_builtin.c \
			srcs/exec/exec_utils.c \
			srcs/exec/exec_andor.c \
			srcs/exec/exec_subshell.c \
			srcs/exec/pipes.c \
			srcs/exec/exec_pipe.c \
			srcs/exec/exec_node.c \
			srcs/echo/echo.c \
			srcs/unset/unset.c \
			srcs/env/env.c \
			srcs/export/sort_env_arr.c \
			srcs/export/export_display.c \
			srcs/export/export.c \
			srcs/pwd/pwd.c \
			srcs/cd/cd.c \
			srcs/cd/update_pwd.c \
			srcs/exit/exit.c \
			srcs/main/get_input.c \
			srcs/main/info_utils.c \
			srcs/main/signals.c \
			srcs/main/main.c

HEADERS	=	include/lexer.h \
			include/syntax_error.h \
			include/environment.h \
			include/parameter_expansion.h \
			include/quote_removal.h \
			include/here_doc.h \
			include/parser.h \
			include/wildcard.h \
			include/path_search.h \
			include/exec_node.h \
			include/minishell.h

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./include

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS} ${LIBFT}
			${CC} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

${LIBFT}:
			make -C libft

%.o:		%.c	${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS}
			make -C libft clean

fclean:		clean
			${RM} ${NAME} ${LIBFT}

re:			fclean all

.PHONY:		all clean fclean re
