/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double_quotes_dollar_expansion.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/15 17:15:23 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_quoted_exp(t_data *data, char *param)
{
	char	quote;
	char	*new_param;
	int		i;
	int		end;
	char	*subtok;
	char	*temp;

	quote = is_quoted(param);
	if (quote)
	{
		new_param = ft_strdup("\0");
		i = 0;
		while ((param[i] != '\0') && (param[i] != '\n'))
		{
			end = get_end(param, i);
			subtok = ft_substr(param, i, end - i + 1);
			if (!subtok)
				return (NULL);
			if (ft_strchr(subtok, '$'))
			{
				remove_quotes(&subtok, data);
				temp = subtok;
				subtok = expand(data, subtok);
				free(temp);
				add_quotes(&subtok, "\'");
			}
			temp = new_param;
			new_param = ft_strjoin(new_param, subtok);
			free(subtok);
			free(temp);
			if (end != (int)ft_strlen(param) + 1)
				i = end + 1;
		}
	}
	else
	{
		manage_expansions(data, &param, 0);
		return (param);
	}
	return (new_param);
}