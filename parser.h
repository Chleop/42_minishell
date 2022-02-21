/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:16:35 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/21 15:19:48 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define EMPTY		999
# define OPERATOR	1
# define RED_IN		3 
# define RED_OUT_S	4
# define RED_OUT_D	5
# define HERE_END	6
# define CMD		7
# define PARAM		8

# define NO_EXP		1
# define EXP		2

struct	s_data;

typedef struct s_lex
{
	char	*input;
	int		i;
	int		tok_nb;
	int		char_nb;
}	t_lex;

//PRINTS
void	print_char_table(char *str, char **tab);
void	print_int_table(int *tab);
void	print_cmds_and_tokens(t_data *data);
void	print_cmd_parameters(t_data *data);

//UTILS FOR ALL
int		add_tab(char ***tab, int *count, char *param);
int		add_int(int **tab, int count, int param);
void	ft_del_stringtab(char ***tab);
int		ft_error(char *str);
void	final_exit(t_data *data);
void	ft_free_parser(t_data *data, char ***token);
void	ft_free_data(t_data *data, int code);

//LEXER
char	**lexer(char *input);
void	create_new_token(char ***token, t_lex *lex);
void	add_to_token(char ***token, t_lex *lex, char input);
int		is_paired(char q, char *input, int i);

void	condition_0(t_lex *lex, char ***token);
void	condition_1(t_lex *lex, char ***token);
void	condition_2(t_lex *lex, char ***token);
void	condition_3(t_lex *lex, char ***token);
void	condition_4(t_lex *lex, char ***token);
void	condition_5(t_lex *lex, char ***token);
void	condition_6(t_lex *lex, char ***token);
void	condition_7(t_lex *lex, char ***token);

//PARSER
int		parse(t_data *data, char **token);
int		initialize_data(t_data *data, char **token);
int		initialize_cmds(t_data *data, char **token);
int		grammatize_tokens(t_data *data);
int		expand_and_set_into_structure(t_data *data);

int		set_into_structure1(t_data *data, char **token, int n, int tok_nr);
int		set_into_structure2(t_data *data, char **token, int n, int tok_nr);
int		set_redirections_tabs(t_data *data, char **token, int n, int qualif);

int		remove_quotes_inside_struct(t_data *data);
int		remove_quotes(char **token);
int		is_quoted(char *token);
int		is_paired(char q, char *input, int i);
int		*locate_c_in_string(char *token, char c, int len);
void	copy_without_tabs(char **new_str, int *index_tab, char *str);

char	*get_expansion(t_data *data, char *to_be_exp);
char	*get_path(t_data *data, char *cmd);

int		manage_expansions(t_data *data, char **token, int here_doc);
char	*double_quoted_exp(t_data *data, char *param);
char	*expand(t_data *data, char *token);

#endif
