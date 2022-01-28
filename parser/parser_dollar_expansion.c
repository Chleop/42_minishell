/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/28 18:07:23 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_param_by_extansion(t_data *data, char *param)
{
	int		i;
	int		j;
	int		len;
	char	*pre_param;
	char	*expanded_param;
	char	*temp;
	char	*needle;
	char	quote[2];

	if (is_quoted(param) && param[0] == '\'')
	{
		identify_remove_quotes(&param);
		return (ft_strdup(param));
	}
	identify_remove_quotes(&param);
	pre_param = NULL;
	expanded_param = NULL;
	temp = NULL;
	j = 0;
	quote[0] = is_quoted(param);
	quote[1] = '\0';
	if (quote[0])
		identify_remove_quotes(&param);
	while (param[j] != '$')
		j++;
	if (j)
		pre_param = ft_substr(param, 0, j);
	needle = ft_strjoin(param + j + 1, "=");
	len = (int)ft_strlen(param) - j;
	i = 0;
	while ((data->envp[i]) && (ft_strlen(needle) != 1))
	{
		if (ft_strnstr(data->envp[i], needle, ft_strlen(needle)))
		{
			expanded_param = ft_substr(data->envp[i], len, (ft_strlen(data->envp[i]) - len));
			break;
		}
		i++;
	}
	free (needle);
	if (quote[0])
	{
		temp = expanded_param;
		expanded_param = ft_strjoin(quote, expanded_param);
		free(temp);
		temp = expanded_param;
		expanded_param = ft_strjoin(expanded_param, quote);
		free(temp);
	}
	if (!expanded_param)
		return (pre_param);
	if (pre_param)
	{
		temp = expanded_param;
		expanded_param = ft_strjoin(pre_param, expanded_param);
		free(temp);
		free(pre_param);
	}

	return (expanded_param);
}

int	ft_param_len(char *str)
{
	int	i;
	int j;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("$", str[i]))
			break ;
		i++;
	}
	i++;
	j = 0;
	while (str[i])
	{
		if (ft_strchr("$", str[i]))
			return (j);
		i++;
		j++;
	}
	return (j);
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
	int	i;
	int	start;
	int	end;
	char	*subtok;
	char	*new_tok;
	char	*temp;

	new_tok = NULL;
	i = 0;
	while ((token[i] != '\0') && (token[i] != '\n'))
	{
		start = i;
		end = get_end(token, i);
		subtok = ft_substr(token, start, end - start + 1);
		if (!subtok)
			return (NULL);
		if (((start == 0) && (end == (int)ft_strlen(token) + 1)) || (ft_strchr(subtok, '$')))
			subtok = replace_param_by_extansion(data, subtok);
		else
			identify_remove_quotes(&subtok);
		temp = new_tok;
		new_tok = ft_strjoin(new_tok, subtok);
		if (temp)
			free (temp);
		if (end == (int)ft_strlen(token) + 1)
			break;
		i = end + 1;
	}
	return (new_tok);
}
