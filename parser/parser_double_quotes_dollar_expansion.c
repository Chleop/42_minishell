/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double_quotes_dollar_expansion.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/31 16:43:23 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_dqe_end(char *param)
{
	int		*quote_i;

	quote_i = ft_calloc(3, sizeof(int));
	quote_i[0] = 0;
	quote_i[1] = 0;
	while ((param[quote_i[0]] != '\0') && (param[quote_i[0]] != '\n'))
	{
		if (((param[quote_i[0]] == '\'') || (param[quote_i[0]] == '\"'))
			&& is_paired(param[quote_i[0]], param, quote_i[0] + 1))
		{
			quote_i[1] = is_paired(param[quote_i[0]], param, quote_i[0] + 1);
			break ;
		}
		quote_i[0]++;
	}
	return (quote_i);
}

char	*join_sub_param(char **env, char **sub_param)
{
	int		i;
	char	*new_param;
	char	*temp;

	new_param = ft_strdup("\0");
	i = 0;
	while (i < 5)
	{
		if (ft_strchr(sub_param[i], '$'))
		{
			temp = sub_param[i];
			sub_param[i] = get_and_expand(env, sub_param[i]);
			free (temp);
		}
		temp = new_param;
		new_param = ft_strjoin(new_param, sub_param[i]);
		free (temp);
		free (sub_param[i]);
		i++;
	}
	return (new_param);
}

char	*double_quoted_exp(t_data *data, char *param)
{
	int		*ind;
	char	*sub_param[5];
	char	*quote;

	ind = get_dqe_end(param);
	quote = ft_calloc(2, sizeof(char));
	quote[0] = param[ind[1]];
	sub_param[0] = ft_substr(param, 0, ind[0]);
	sub_param[1] = quote;
	sub_param[2] = ft_substr(param, ind[0] + 1, ind[1] - ind[0] - 1);
	sub_param[3] = ft_strdup(quote);
	sub_param[4] = ft_substr(param, ind[1] + 1, ft_strlen(param) - ind[1] - 1);
	free(ind);
	return (join_sub_param(data->envp, sub_param));
}
