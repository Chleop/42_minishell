# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 12:28:36 by cproesch          #+#    #+#              #
#    Updated: 2022/01/20 12:45:25 by cproesch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c utils_for_all.c print_functions.c \
			lexer/lexer.c lexer/lexer_functions_1.c lexer/lexer_functions_2.c \
			lexer/lexer_utils.c \
			parser/parser.c parser/parser_initialization.c parser/parser_utils.c \
			parser/parser_grammar.c parser/parser_qualification.c

OBJS		= $(SRCS:.c=.o)

NAME		= minishell

CC			= clang

IFLAGS		= -I. -Ilibft

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3 $(IFLAGS)

LFLAGS		= -Llibft -lft 

RM			= rm -rf

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) $(OBJS) $(LFLAGS) $(CFLAGS) -o $(NAME) -v -lreadline

all:		$(NAME)

clean:	
			make -C libft -f Makefile clean
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			make -C libft -f Makefile fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re