# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 15:32:57 by avan-bre          #+#    #+#              #
#    Updated: 2022/02/23 12:12:58 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                 COMPILATION                                  #
################################################################################

NAME	=	minishell
LIBFT	=	libft/libft.a
RM		=	@rm -rf
CC		=	@clang
IFLAGS	=	-I. -Ilibft
RLFLAGS	=	-lreadline
CFLAGS	:=	-Wall -Werror -Wextra $(IFLAGS)
LFLAGS	:=	-Llibft -lft

################################################################################
#                                    FILES                                     #
################################################################################

SRCS	=	$(addprefix $(M_DIR), $(M_SRCS)) $(addprefix $(E_DIR), $(E_SRCS)) \
			$(addprefix $(L_DIR), $(L_SRCS)) $(addprefix $(P_DIR), $(P_SRCS))
M_SRCS	=	main.c set_envp.c envp_utils.c utils_for_all.c free_utils.c \
			print_functions.c signals.c
E_SRCS	=	redirection.c pipes.c exec.c BI_cd.c BI_cd2.c BI_cd3.c BI_env_echo_pwd.c \
			BI_export.c BI_export2.c BI_unset.c BI_exit.c free_exec.c
L_SRCS	=	lexer.c lexer_functions_1.c lexer_functions_2.c lexer_utils.c
P_SRCS	=	parser_step_1.c data_initialization.c commands_initialization.c grammar.c \
			parser_step_2.c set_into_structure.c set_redirection_tabs_and_here_doc.c \
			dollar_expansion.c double_quoted_dollar_expansion.c \
			quotes_removal.c quotes_removal_utils.c parser_command_path.c
M_DIR	=	main/
E_DIR	=	execution/
L_DIR	=	lexer/
P_DIR	=	parser/
O_DIR	=	objects/
OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))

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

clean:
	$(RM) $(OBJS) $(E_OBJS) ${B_OBJS}
	@make $@ -s -C libft
	@echo "Removed objects"

fclean:		clean
	$(RM) $(NAME) ${B_NAME}
	@make $@ -s -C libft
	@echo "Removed executable files"

re:			fclean all

.PHONY:		re, all, clean, fclean
