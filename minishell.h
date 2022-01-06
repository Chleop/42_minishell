/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:03:39 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/06 15:14:06 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_lex
{
	char	*input;
	int		i;
	int		token_nb;
	int		tok_char_nb;
}	t_lex;

void	print_table(char **tab);
void	ft_del_stringtab(char ***tab);
char	**split_into_token(char *input);

void	function_0(t_lex *lex, char ***token);
void	function_1(t_lex *lex, char ***token);
void	function_2(t_lex *lex, char ***token);
void	function_3(t_lex *lex, char ***token);
void	function_4(t_lex *lex, char ***token);
void	function_5(t_lex *lex, char ***token);
void	function_6(t_lex *lex, char ***token);

#endif