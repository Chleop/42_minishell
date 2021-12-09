# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 12:28:36 by cproesch          #+#    #+#              #
#    Updated: 2021/12/09 12:29:59 by cproesch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/main_bonus.c src/find_path_bonus.c \
			src/del_exit_utils_bonus.c src/process_bonus.c \
			src/process_utils_bonus.c

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
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

all:		$(NAME)

clean:	
			make -C libft -f Makefile clean
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			make -C libft -f Makefile fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re