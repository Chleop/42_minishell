/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/31 16:00:14 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expansion(char **env, char *token, int j)
{
	int		len;
	char	*needle;
	char	*exp;

	needle = ft_strjoin(token + j + 1, "=");
	len = (int)ft_strlen(token) - j;
	exp = ft_strdup("\0");
	j = 0;
	while ((env[j]) && (ft_strlen(needle) != 1))
	{
		if (ft_strnstr(env[j], needle, ft_strlen(needle)))
		{
			exp = ft_substr(env[j], len, (ft_strlen(env[j]) - len));
			break ;
		}
		j++;
	}
	free (needle);
	return (exp);
}

char	*get_and_expand(char **env, char *token)
{
	int		i;
	char	*expanded_token;
	char	*pre_param;
	char	*exp;

	i = 0;
	while (token[i] != '$')
		i++;
	pre_param = ft_substr(token, 0, i);
	exp = get_expansion(env, token, i);
	expanded_token = ft_strjoin(pre_param, exp);
	free(exp);
	free(pre_param);
	return (expanded_token);
}

char	*replace_param_by_expansion(t_data *data, char *param)
{
	int		quote;

	if (!ft_strchr(param, '$'))
	{
		identify_remove_quotes(&param);
		return (param);
	}
	else
	{
		quote = is_quoted(param);
		identify_remove_quotes(&param);
		if (quote == '\'')
			return (ft_strdup(param));
		if ((quote == '\"') && is_quoted(param))
			return (double_quoted_exp(data, param));
		return (get_and_expand(data->envp, param));
	}
}

int	get_end(char *token, int i)
{
	if (((token[i] == '\'') || (token[i] == '\"'))
		&& is_paired(token[i], token, i + 1))
		return (is_paired(token[i], token, i + 1));
	else
	{
		i++;
		while ((token[i] != '\0') && (token[i] != '\n')
			&& (token[i] != '\'') && (token[i] != '\"')
			&& (token[i] != '$'))
			i++;
		return (i - 1);
	}
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
		if (temp)
			free (temp);
		if (end != (int)ft_strlen(token) + 1)
			i = end + 1;
	}
	return (new_tok);
}
