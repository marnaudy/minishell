# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 17:15:05 by marnaudy          #+#    #+#              #
#    Updated: 2022/05/11 15:24:50 by marnaudy         ###   ########.fr        #
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
			srcs/parser/parser_utils.c \
			srcs/parser/add_redirection.c \
			srcs/parser/new_command_node.c \
			srcs/parser/add_operator.c \
			tester.c

HEADERS	=	lexer.h \
			syntax_error.h \
			environment.h \
			minishell.h

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./include -g

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
