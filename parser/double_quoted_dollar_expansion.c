/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quoted_dollar_expansion.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/18 15:23:52 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end2(char *token, int i, int j)
{
	if (j == 0)
	{
		while (token[i] != '$')
			i++;
		return (i);
	}
	if (ft_strchr(token + i, '$'))
	{
		if ((token[i] == '\'') || (token[i] == '$')
			|| (token[i] == ' '))
			i++;
		while ((token[i] != '\'') && (token[i] != '\"') && (token[i] != '$')
			&& (token[i] != ' ') && (token[i] != '\0') && (token[i] != '\n'))
			i++;
	}
	else
		return (ft_strlen(token));
	return (i);
}

void	if_dollar_expand(t_data *data, char **subtok)
{
	char	*temp;

	if (ft_strchr(*subtok, '$'))
	{
		temp = *subtok;
		*subtok = expand(data, *subtok);
		free(temp);
	}
}

void	join_subtok(char **subtok, char **new_param)
{
	char	*temp;

	temp = *new_param;
	*new_param = ft_strjoin(*new_param, *subtok);
	free(temp);
}

char	*double_quoted_exp(t_data *data, char *param)
{
	char	*new_param;
	int		i;
	int		j;
	int		end;
	char	*subtok;

	j = 0;
	new_param = ft_strdup("\0");
	i = 0;
	while (((param[i] != '\0') && (param[i] != '\n')))
	{
		end = get_end2(param, i, j);
		j++;
		subtok = ft_substr(param, i, end - i);
		if_dollar_expand(data, &subtok);
		join_subtok(&subtok, &new_param);
		free(subtok);
		i = end;
	}
	return (new_param);
}
