/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 10:42:39 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_and_expand(t_data *data, char *token)
// {
// 	int		i;
// 	char	*expanded_token;
// 	char	*pre_param;
// 	char	*exp;

// 	i = 0;
// 	while (token[i] != '$')
// 		i++;
// 	pre_param = ft_substr(token, 0, i);
// 	exp = get_expansion(data, token + i + 1);
// 	expanded_token = ft_strjoin(pre_param, exp);
// 	free(exp);
// 	free(pre_param);
// 	return (expanded_token);
// }

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

char	*get_and_expand(t_data *data, char *token)
{
	char	**sub_param;
	char	*param;

	sub_param = NULL;
	if (ft_strchr(token, ' '))
	{
		sub_param = ft_split(token, ' ');
		param = join_and_expand_subparam(data, sub_param, " ");
	}
	else
		param = expand(data, token);
	return (param);
}

// If a dollar is found within the subtoken and is not single quoted
// expands it

char	*replace_param_by_expansion(t_data *data, char *param)
{
	int		quote;

	if (!ft_strchr(param, '$'))
		return (ft_strdup(param));
	else
	{
		quote = is_quoted(param);
		if (quote == '\'')
			return (ft_strdup(param));
		if (quote == '\"')
			return (double_quoted_exp(data, param));
		param = get_and_expand(data, param);
		return (param);
	}
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

char	*manage_expansions(t_data *data, char *token)
{
	int		i;
	int		end;
	char	*subtok;
	char	*new_tok;
	char	*temp;

	new_tok = ft_strdup("\0");
	i = 0;
	printf("inside manage expansion, token = %s\n", token);
	while ((token[i] != '\0') && (token[i] != '\n'))
	{
		end = get_end(token, i);
		subtok = ft_substr(token, i, end - i + 1);
		printf ("subtok before exp is : %s\n", subtok);
		if (!subtok)
			return (NULL);
		temp = subtok;
		subtok = replace_param_by_expansion(data, subtok);
		printf ("subtok after exp is : %s\n", subtok);
		free (temp);
		temp = new_tok;
		new_tok = ft_strjoin(new_tok, subtok);
		free(subtok);
		free(temp);
		if (end != (int)ft_strlen(token) + 1)
			i = end + 1;
	}
	return (new_tok);
}
