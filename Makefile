# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 12:28:36 by cproesch          #+#    #+#              #
#    Updated: 2022/01/11 11:15:08 by cproesch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c lexer/lexer.c lexer/lexer_functions_1.c lexer/lexer_functions_2.c \
			lexer/lexer_utils.c utils_for_all.c

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
			$(CC) $(OBJS) $(LFLAGS) $(CFLAGS) -o $(NAME) -v

all:		$(NAME)

clean:	
			make -C libft -f Makefile clean
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			make -C libft -f Makefile fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re