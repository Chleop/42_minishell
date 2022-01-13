/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:03:39 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/13 16:39:00 by cproesch         ###   ########.fr       */
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

struct s_cmd;

typedef struct s_data
{
	char			**envp;
	int				nr_cmds;
	struct s_cmd	*cmd;
	int				pipe_fd[1023][2];
	int				process_id[1024];
}	t_data;

typedef struct s_lex
{
	char	**envp;
	char	*input;
	int		i;
	int		token_nb;
	int		tok_char_nb;
}	t_lex;

typedef struct s_cmd
{
	char	**params;
	char	*i_file;
	char	*o_file;
	int		cmd_id;
} t_cmd;

char	**split_into_token(char *input, char **envp);
void	create_new_token(char ***token, t_lex *lex);
void	add_to_token(char ***token, t_lex *lex, char input);
int		is_paired(char q, char *input, int i);
void	manage_expansions(t_lex *lex, char **token);

void	condition_0(t_lex *lex, char ***token);
void	condition_1(t_lex *lex, char ***token);
void	condition_2(t_lex *lex, char ***token);
void	condition_3(t_lex *lex, char ***token);
void	condition_4(t_lex *lex, char ***token);
void	condition_5(t_lex *lex, char ***token);
void	condition_6(t_lex *lex, char ***token);
void	condition_7(t_lex *lex, char ***token);

void	print_table(char **tab);
void	ft_del_stringtab(char ***tab);

#endif