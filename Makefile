# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 12:28:36 by cproesch          #+#    #+#              #
#    Updated: 2022/01/06 15:03:51 by cproesch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c lexer/lexer.c lexer/lexer_functions.c lexer/lexer_utils.c

OBJS		= $(SRCS:.c=.o)

NAME		= minishell

CC			= clang

IFLAGS		= -I. -Ilibft

CFLAGS		= -Wall -Wextra -Werror $(IFLAGS)

LFLAGS		= -Llibft -lft 

RM			= rm -rf

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME) -v

all:		$(NAME)

clean:	
			make -C libft -f Makefile clean
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			make -C libft -f Makefile fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re