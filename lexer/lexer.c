/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:20:21 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 11:31:01 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_lex *lex, char *input)
{
	lex->input = input;
	lex->i = 0;
	lex->tok_nb = 0;
	lex->char_nb = 0;
}

int	condition_tree(t_lex *lex, char ***token)
{
	if (!(*token))
		return (0);
	if ((lex->i > 0) && (ft_strchr("|<>", (lex->input)[lex->i - 1])))
		return (1);
	if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
		return (2);
	if ((lex->input)[lex->i] == '$')
		return (3);
	if (ft_strchr("|<>", (lex->input)[lex->i]))
		return (4);
	if ((lex->input)[lex->i] == ' ')
		return (5);
	if ((lex->i > 0) && (!(ft_strchr("|<> ", (lex->input)[lex->i - 1]))))
		return (6);
	return (7);
}

char	**lexer(char *input)
{
	t_lex		lex;
	char		**token;
	int			met_condition;
	static void	(*function_table[9])(t_lex *lex, char ***token) = {
		condition_0, condition_1, condition_2, condition_3, condition_4,
		condition_5, condition_6, condition_7, NULL,
	};

		init_lexer(&lex, input);
	token = NULL;
	while (((lex.input)[lex.i] != '\n') && ((lex.input)[lex.i] != '\0'))
	{
		met_condition = condition_tree(&lex, &token);
		function_table[met_condition](&lex, &token);
	}
	free (lex.input);
	return (token);
}
