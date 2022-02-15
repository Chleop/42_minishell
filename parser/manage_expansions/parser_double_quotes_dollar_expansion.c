/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double_quotes_dollar_expansion.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/15 19:25:29 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end2(char *token, int i, int j)
{
	if (j == 0)
	{
		while (token[i] != '$')
			i++;
	}
	else if (j == 1)
	{
		if ((token[i] == '$') || (token[i] == '\''))
			i++;
		while ((token[i] != '\0') && (token[i] != '\n')
			&& (token[i] != '\'') && (token[i] != '$')
			&& (token[i] != ' '))
			i++;
	}
	else
	{
		while ((token[i] != '\0') && (token[i] != '\n')
			&& (token[i] != '$'))
			i++;
	}
	return (i);
}

char	*double_quoted_exp(t_data *data, char *param)
{
	char	quote;
	char	*new_param;
	int		i;
	int		j;
	int		end;
	char	*subtok;
	char	*temp;

	j = 0;
	quote = is_quoted(param);
	if (quote)
	{
		new_param = ft_strdup("\0");
		i = 0;
		while ((param[i] != '\0') && (param[i] != '\n'))
		{
			end = get_end2(param, i, j);
			j++;
			subtok = ft_substr(param, i, end - i);
			if (ft_strchr(subtok, '$'))
			{
				temp = subtok;
				subtok = expand(data, subtok);
				free(temp);
			}
			temp = new_param;
			new_param = ft_strjoin(new_param, subtok);
			free(subtok);
			free(temp);
			if (end != (int)ft_strlen(param) + 1)
				i = end;
		}
	}
	else
	{
		manage_expansions(data, &param, 0);
		return (param);
	}
	return (new_param);
}
