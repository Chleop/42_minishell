/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 12:42:30 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expansion(t_data *data, char *token, int j)
{
	char	*exp;
	t_envp	*temp;

	exp = ft_strdup("\0");
	temp = data->envp;
	while (temp && ft_strlen(token + j))
	{
		if (!ft_strncmp(temp->name, token + j + 1, ft_strlen(temp->name) + 1))
		{
			exp = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	return (exp);
}

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
	exp = get_expansion(data, token, i);
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
		return (get_and_expand(data, param));
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
