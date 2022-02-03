/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:16:35 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/03 13:04:52 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define EMPTY		999
# define OPERATOR	1
// # define VAR		2
# define RED_IN		3 
# define RED_OUT_S	4
# define RED_OUT_D	5
# define HERE_END	6
# define CMD		7
# define PARAM		8

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
void	final_exit(t_data *data, int i, char *str);
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
int		initialize_data(t_data *data, char **token);
int		set_end(t_data *data, int i);
int		divide_token(t_data *data, char **token, int *start, int i);
int		initialize_cmds(t_data *data, char **token);
int		grammatize_tokens(t_data *data);

int		count_token(char **token);
int		localize_pipes(t_data *data, char **token);
int		parse(t_data *data, char **token);
char	*get_expansion(t_data *data, char *to_be_exp);
char	*get_path(t_data *data, char *cmd);

int		set_into_structure(t_data *data);
int		expand_and_classify_dollars(t_data *data);
int		is_quoted(char *token);
int		identify_remove_quotes(char **token);
int		remove_quotes(char **token, int firstq_i, int secondq_i);
int		classify_others(t_data *data);
char	*manage_expansions(t_data *data, char *token);
int		classify_token(t_data *data, char **token, int cmd_nr, int tok_nr);
void	expand_cmd_path(t_data *data);
char	*double_quoted_exp(t_data *data, char *param);
char	*get_and_expand(t_data *data, char *token);

#endif
