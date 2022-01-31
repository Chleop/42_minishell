/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansions_double_quotes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/31 14:02:30 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *get_dqe_end(char *param)
{
    int		*quote_index;

    quote_index = ft_calloc(3, sizeof(int));
    quote_index[0] = 0;
	quote_index[1] = 0;
    while ((param[quote_index[0]] != '\0') && (param[quote_index[0]] != '\n'))
	{
		if (((param[quote_index[0]] == '\'') || (param[quote_index[0]] == '\"'))
			&& is_paired(param[quote_index[0]], param, quote_index[0] + 1))
		{
			quote_index[1] = is_paired(param[quote_index[0]], param, quote_index[0] + 1);
			break;
		}
		quote_index[0]++;
	}
    return (quote_index);
}

char    *join_sub_param(char **env, char **sub_param)
{
    int     i;
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
	int		*quote_index;
	char	*sub_param[5];
	char	*quote;

	quote_index = get_dqe_end(param);
	quote = ft_calloc(2, sizeof(char));
	quote[0] = param[quote_index[1]];
	sub_param[0] = ft_substr(param, 0, quote_index[0]);
	sub_param[1] = quote;
	sub_param[2] = ft_substr(param, quote_index[0] + 1, quote_index[1] - quote_index[0] - 1);
	sub_param[3] = ft_strdup(quote);
	sub_param[4] = ft_substr(param, quote_index[1] + 1, ft_strlen(param) - quote_index[1] - 1);
    free(quote_index);
	return (join_sub_param(data->envp, sub_param));
}