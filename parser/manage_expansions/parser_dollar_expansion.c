/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/15 17:15:38 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(t_data *data, char *token)
{
	int		i;
	char	*expanded_token;
	char	*pre_param;
	char	*exp;

	i = 0;
	while (token[i] != '$')
		i++;
	pre_param = ft_substr(token, 0, i);
	exp = get_expansion(data, token + i + 1);
	expanded_token = ft_strjoin(pre_param, exp);
	free(exp);
	free(pre_param);
	return (expanded_token);
}

// If the token cotaining a $ is single quoted, returns the token unchanged
// Ifit is doubled quoted, applies the double_quoted_expansion function
// Else, expands the token (using the expand function directly, considering
// that if there are no quotes, then there are no spaces either)

char	*replace_subtok_by_expansion(t_data *data, char **param, int here_doc)
{
	int		quote;
	char	*new_param;

	quote = is_quoted(*param);
	remove_quotes(param, data);
	if (!here_doc && quote == '\'')
		new_param = ft_strdup(*param);
	else 
	{
		if (here_doc || quote == '\"')
			new_param = double_quoted_exp(data, *param);
		else
			new_param = expand(data, *param);
	}
	free(*param);
	return (new_param);
}

// Determines the end of each subtoken depending on whether there are paired
// quotes, dollars or end of token
// if the token[i] is a quote and is paired, the end of subtok is the paired 
// quote otherwise the end of the subtoken is the end of the token, or before 
// a quote, or before a $ 

int	get_end(char *token, int i)
{
	if (((token[i] == '\'') || (token[i] == '\"'))
		&& is_paired(token[i], token, i + 1))
		return (is_paired(token[i], token, i + 1));
	i++;
	while ((token[i] != '\0') && (token[i] != '\n')
		&& (token[i] != '\'') && (token[i] != '\"')
		&& (token[i] != '$') && (token[i] != ' '))
		i++;
	return (i - 1);
}

// Browses the token char by char until its end
// Identifies the end of each subtoken
// Creates each subtoken
// Expands the subtoken if needed
// Joins the subtoken to the preceding ones
// Sets the start of the next subtoken to the end of the preceding one + 1

int	manage_expansions(t_data *data, char **token, int here_doc)
{
	int		i;
	int		end;
	char	*subtok;
	char	*new_tok;
	char	*temp;

	new_tok = ft_strdup("\0");
	i = 0;
	while (((*token)[i] != '\0') && ((*token)[i] != '\n'))
	{
		end = get_end((*token), i);
		subtok = ft_substr((*token), i, end - i + 1);
		if (!subtok)
			return (0);
		if (ft_strchr(subtok, '$'))
			subtok = replace_subtok_by_expansion(data, &subtok, here_doc);
		temp = new_tok;
		new_tok = ft_strjoin(new_tok, subtok);
		free(subtok);
		free(temp);
		if (end != (int)ft_strlen((*token)) + 1)
			i = end + 1;
	}
	temp = *token;
	*token = new_tok;
	free(temp);
	return (1);
}
