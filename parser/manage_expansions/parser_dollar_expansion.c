/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/04 15:39:03 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_and_expand(t_data *data, char *token)
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

char	*replace_param_by_expansion(t_data *data, char *param)
{
	int		quote;
	char	*temp;

	if (!ft_strchr(param, '$'))
	{
		if (!identify_remove_quotes(&param))
		{
			ft_error2("Error: malloc failed", data, 1);
			return (NULL);
		}
		return (param);
	}
	else
	{
		quote = is_quoted(param);
		if (!identify_remove_quotes(&param))
		{
			ft_error2("Error: malloc failed", data, 1);
			return (NULL);
		}
		if (quote == '\'')
			return (ft_strdup(param));
		if ((quote == '\"') && is_quoted(param))
			return (double_quoted_exp(data, param));
		temp = param;
		param = get_and_expand(data, param);
		free (temp);
		return (param);
	}
}

int	get_end(char *token, int i)
{
	if (((token[i] == '\'') || (token[i] == '\"'))
		&& is_paired(token[i], token, i + 1))
		return (is_paired(token[i], token, i + 1));
	i++;
	while ((token[i] != '\0') && (token[i] != '\n')
		&& (token[i] != '\'') && (token[i] != '\"')
		&& (token[i] != '$'))
		i++;
	return (i - 1);
}

char	*manage_expansions(t_data *data, char *token)
{
	int		i;
	int		end;
	char	*subtok;
	char	*new_tok;
	char	*temp;

	new_tok = NULL;
	i = 0;
	while ((token[i] != '\0') && (token[i] != '\n'))
	{
		end = get_end(token, i);
		subtok = ft_substr(token, i, end - i + 1);
		if (!subtok)
			return (NULL);
		subtok = replace_param_by_expansion(data, subtok);
		temp = new_tok;
		new_tok = ft_strjoin(new_tok, subtok);
		free(subtok);
		if (temp)
			free (temp);
		if (end != (int)ft_strlen(token) + 1)
			i = end + 1;
	}
	return (new_tok);
}
