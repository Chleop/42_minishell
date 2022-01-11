/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:28:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/07 14:29:08 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_0(t_lex *lex, char ***token)
{
	printf("cond 0\n");
	create_new_token(token, lex);
}

void	condition_1(t_lex *lex, char ***token)
{
	printf("cond 1\n");
	if (ft_strchr("|<>", (lex->input)[lex->i]))
		add_to_token(token, lex, (lex->input)[lex->i++]);
	else if ((lex->input)[lex->i] != '\n')
	{
		create_new_token(token, lex);
		if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
			condition_2(lex, token);
		else
			add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	condition_2(t_lex *lex, char ***token)
{
	char	c;

	printf("cond 2\n");
	c = lex->input[lex->i];
	add_to_token(token, lex, (lex->input)[lex->i++]);
	if ((is_paired(c, lex->input, lex->i)))
	{
		while (lex->input[lex->i] != c)
			add_to_token(token, lex, (lex->input)[lex->i++]);
		add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	condition_3(t_lex *lex, char ***token)
{
	printf("cond 3\n");
	add_to_token(token, lex, (lex->input)[lex->i++]);
	while (((lex->input)[lex->i] != ' ') && ((lex->input)[lex->i] != '\n'))
	{
		if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
			condition_2(lex, token);
		else if ((lex->input)[lex->i] == '$')
			condition_3(lex, token);
		else
			add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	condition_4(t_lex *lex, char ***token)
{
	printf("cond 4\n");
	if (lex->token_nb != 0)
		create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}
