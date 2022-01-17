/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:38:33 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/14 16:16:42 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_token(char ***token, t_lex *lex)
{
	int		l;
	char	**tab_temp;

	while ((lex->input)[lex->i] == ' ')
		lex->i++;
	if ((lex->input)[lex->i] == '\n')
		return ;
	if ((!(*token)) || (lex->tok_char_nb != 0))
	{
		lex->tok_char_nb = 0;
		lex->token_nb = (lex->token_nb) + 1;
		tab_temp = (*token);
		*token = ft_calloc((lex->token_nb + 1), sizeof(char *));
		if (tab_temp)
		{
			l = 0;
			while (tab_temp[l])
			{
				(*token)[l] = tab_temp[l];
				l++;
			}
			free(tab_temp);
		}
	}
}

void	add_to_token(char ***token, t_lex *lex, char input)
{
	int		l;
	char	*str_temp;

	if (input != '\n')
	{
		lex->tok_char_nb = lex->tok_char_nb + 1;	
		str_temp = (*token)[lex->token_nb - 1];
		(*token)[lex->token_nb - 1] = ft_calloc((lex->tok_char_nb + 1), sizeof(char));
		if (str_temp)
		{
			l = 0;
			while (str_temp[l])
			{
				(*token)[lex->token_nb - 1][l] = str_temp[l];
				l++;
			}
			free(str_temp);
		}
		(*token)[lex->token_nb - 1][lex->tok_char_nb - 1] = input;
	}
}

int	is_paired(char q, char *input, int i)
{
	while (input[i])
	{
		if (input[i] == q)
			return (1);
		i++;
	}
	return (0);
}
