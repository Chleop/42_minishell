# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 10:49:58 by avan-bre          #+#    #+#              #
#    Updated: 2021/08/09 18:15:42 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc -c -o 

AR 		=	ar rcs

RM		=	rm -rf

INC		=	ft_printf.h

SRCS	=	ft_printf.c \
			ft_printf_utils.c \
			print_char.c \
			print_string.c \
			print_int.c \
			print_uns_int.c \
			print_hex.c \
			print_hex_cap.c \
			print_ptr.c \

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

$(NAME):	$(OBJS)
	$(AR) $(NAME) $(OBJS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		clean all

.PHONY:	re, all, clean, fclean, bonus
	
