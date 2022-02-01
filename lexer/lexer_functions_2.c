/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:29:57 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 11:28:51 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_5(t_lex *lex, char ***token)
{
	while ((lex->input)[lex->i] == ' ')
		lex->i++;
	create_new_token(token, lex);
}

void	condition_6(t_lex *lex, char ***token)
{
	add_to_token(token, lex, (lex->input)[lex->i++]);
}

void	condition_7(t_lex *lex, char ***token)
{
	if (lex->char_nb != 0)
		create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}
