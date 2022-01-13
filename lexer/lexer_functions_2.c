/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:29:57 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/12 16:55:42 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_5(t_lex *lex, char ***token)
{
	// printf("cond 5\n");
	while ((lex->input)[lex->i] == ' ')
		lex->i++;
	create_new_token(token, lex);
}

void	condition_6(t_lex *lex, char ***token)
{
	// printf("cond 6\n");
	add_to_token(token, lex, (lex->input)[lex->i++]);
}

void	condition_7(t_lex *lex, char ***token)
{
	// printf("cond 7\n");
	if (lex->tok_char_nb != 0)
		create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}
