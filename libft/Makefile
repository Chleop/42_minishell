SRCS	= ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memset.c ft_strlen.c ft_tolower.c \
ft_toupper.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
ft_memcmp.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c \
ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_itoa.c \
get_next_line_utils.c get_next_line.c printf/ft_printf.c \
printf/print_char.c printf/print_hex.c \
printf/print_int.c printf/print_hex_cap.c printf/print_ptr.c \
printf/print_string.c printf/print_uns_int.c $(SRCS_B)

SRCS_B	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS	= $(SRCS:.c=.o)

OBJS_B	= $(SRCS_B:.c=.o)

NAME	= libft.a

CC		= gcc -c -o

RM		= rm -rf

AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror -Ift_printf

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

all:		$(NAME)

clean:	
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(OBJS) $(OBJS_B)
			$(AR) $(NAME) $(OBJS) $(OBJS_B)

.PHONY:		all clean fclean re bonus
