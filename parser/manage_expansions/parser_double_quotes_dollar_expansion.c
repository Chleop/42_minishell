/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double_quotes_dollar_expansion.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 12:30:42 by cproesch         ###   ########.fr       */
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

char	*join_and_expand_subparam(t_data *data, char **sub_param, char *c)
{
	int		i;
	char	*new_param;
	char	*temp;
	char	**param;
	char	quote;

	new_param = ft_strdup(c);
	i = 0;
	while (sub_param[i])
	{
		if (ft_strchr(sub_param[i], '$'))
		{
			quote = is_quoted(sub_param[i]);
			temp = sub_param[i];
			if (quote)
			{
				param = ft_split(sub_param[i], '\'');
				sub_param[i] = join_and_expand_subparam(data, param, "\'");
				free (param);
				// sub_param[i] = double_quoted_exp(data, sub_param[i]);
			}
			else
				sub_param[i] = expand(data, sub_param[i]);
			free (temp);
		}
		temp = new_param;
		new_param = ft_strjoin(new_param, sub_param[i]);
		free (temp);
		// free (sub_param[i]);
		if (c)
		{
			temp = new_param;
			new_param = ft_strjoin(new_param, c);
			free (temp);
		}
		i++;
	}
	return (new_param);
}

// char	*double_quoted_exp(t_data *data, char *param)
// {
// 	int		*ind;
// 	char	*sub_param[6];
// 	char	*quote;

// 	ind = get_dqe_end(param);
// 	quote = ft_calloc(2, sizeof(char));
// 	quote[0] = param[ind[1]];
// 	sub_param[0] = ft_substr(param, 0, ind[0]);
// 	sub_param[1] = quote;
// 	sub_param[2] = ft_substr(param, ind[0] + 1, ind[1] - ind[0] - 1);
// 	sub_param[3] = ft_strdup(quote);
// 	sub_param[4] = ft_substr(param, ind[1] + 1, ft_strlen(param) - ind[1] - 1);
// 	sub_param[5] = NULL;
// 	free(ind);
// 	return (join_sub_param(data, sub_param));
// }

char	*double_quoted_exp(t_data *data, char *param)
{
	char	**sub_param;
	
	sub_param = ft_split(param, '\"');
	param = join_and_expand_subparam(data, sub_param, "\"");
	free (sub_param);
	return (param);
}