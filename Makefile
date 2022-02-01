# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 15:32:57 by avan-bre          #+#    #+#              #
#    Updated: 2022/02/01 13:04:59 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                 COMPILATION                                  #
################################################################################

NAME	=	minishell
B_NAME	=	
LIBFT	=	libft/libft.a
RM		=	@rm -rf
CC		=	@clang
IFLAGS	=	-I. -Ilibft
RLFLAGS	=	-lreadline
SFLAGS	=	#-fsanitize=address -g3 
CFLAGS	:=	-Wall -Werror -Wextra $(IFLAGS) $(SFLAGS)
LFLAGS	:=	-Llibft -lft

################################################################################
#                                    FILES                                     #
################################################################################

SRCS	=	$(addprefix $(M_DIR), $(M_SRCS)) $(addprefix $(E_DIR), $(E_SRCS)) \
			$(addprefix $(L_DIR), $(L_SRCS)) $(addprefix $(P_DIR), $(P_SRCS))
M_SRCS	=	main.c set_envp.c envp_utils.c utils_for_all.c free_utils.c \
			print_functions.c 
E_SRCS	=	redirection.c pipes.c exec.c BI_cd.c BI_cd2.c BI_env_echo_pwd.c \
			BI_export.c BI_export2.c BI_unset.c BI_exit.c
L_SRCS	=	lexer.c lexer_functions_1.c lexer_functions_2.c lexer_utils.c
P_SRCS	=	parser.c parser_initialization.c parser_utils.c parser_grammar.c \
			parser_quotes_removal.c	parser_struct_utils.c parser_set_structure.c \
			parser_dollar_expansion.c parser_command_path.c \
			parser_double_quotes_dollar_expansion.c
#B_SRCS	=	
#S_DIR	=	sources/
#B_DIR	=	bonus_sources/
M_DIR	=	main/
E_DIR	=	execution/
L_DIR	=	lexer/
P_DIR	=	parser/
O_DIR	=	objects/
OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))
#B_OBJS	=	$(addprefix $(B_DIR), $(B_SRCS:.c=.o))

################################################################################
#                                 RULES                                        #
################################################################################

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	@echo "Compiling sources.."
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $@ $(RLFLAGS)
	@echo "Ready!"

$(LIBFT):
	@echo "Compiling libft.."
	@make -s -C libft
	@echo "Libft ready!"

#bonus:	${B_OBJS} ${LIBFT}
#	@echo "Compiling bonus sources.."
#	${CC} ${B_OBJS} ${LFLAGS} -o ${B_NAME}
#	@echo "Ready!"

clean:
	$(RM) $(OBJS) $(E_OBJS) ${B_OBJS}
	@make $@ -s -C libft
	@echo "Removed objects"

fclean:		clean
	$(RM) $(NAME) ${B_NAME}
	@make $@ -s -C libft
	@echo "Removed executable files"

re:			clean all

.PHONY:		re, all, clean, fclean