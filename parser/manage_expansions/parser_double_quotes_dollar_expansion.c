/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double_quotes_dollar_expansion.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 16:51:50 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	*get_dqe_end(char *param)
// {
// 	int		*quote_i;

// 	quote_i = ft_calloc(3, sizeof(int));
// 	quote_i[0] = 0;
// 	quote_i[1] = 0;
// 	while ((param[quote_i[0]] != '\0') && (param[quote_i[0]] != '\n'))
// 	{
// 		if (((param[quote_i[0]] == '\'') || (param[quote_i[0]] == '\"'))
// 			&& is_paired(param[quote_i[0]], param, quote_i[0] + 1))
// 		{
// 			quote_i[1] = is_paired(param[quote_i[0]], param, quote_i[0] + 1);
// 			break ;
// 		}
// 		quote_i[0]++;
// 	}
// 	return (quote_i);
// }


// void expansion_something()
// {
// 		if (ft_strchr(sub_param[i], '$'))
// 		{
// 			quote = is_quoted(sub_param[i]);
// 			temp = sub_param[i];
// 			if (quote)
// 			{
// 				param = ft_split(sub_param[i], '\'');
// 				sub_param[i] = join_and_expand_subparam(data, param, "\'");
// 				free (param);
// 			}
// 			else
// 				sub_param[i] = expand(data, sub_param[i]);
// 			free (temp);
// 		}
// }

// char	*double_quoted_exp(t_data *data, char *param)
// {
// 	int		i;
// 	char	*new_param;
// 	char	*temp;
// 	char	**param_tab;
// 	char	quote;
// 	char	**sub_param;
	
// 	sub_param = ft_split(param, '\"');
// 	new_param = ft_strdup("\0");
// 	i = 0;
// 	while (sub_param[i])
// 	{
// 		if (ft_strchr(sub_param[i], '$'))
// 		{
// 			quote = is_quoted(sub_param[i]);
// 			temp = sub_param[i];
// 			if (quote)
// 			{
// 				param_tab = ft_split(sub_param[i], '\'');
// 				sub_param[i] = join_and_expand_subparam(data, param_tab, "\'");
// 				ft_del_stringtab(param_tab);
// 			}
// 			else
// 				sub_param[i] = get_and_expand(data, sub_param[i]);
// 			free (temp);
// 		}
// 		temp = new_param;
// 		new_param = ft_strjoin(new_param, sub_param[i]);
// 		free (temp);
// 		// free (sub_param[i]);
// 		if (c)
// 		{
// 			temp = new_param;
// 			new_param = ft_strjoin(new_param, "\"");
// 			free (temp);
// 		}
// 		i++;
// 	}
// 	ft_del_stringtab(sub_param);
// 	return (new_param);
// }

char	*join_and_expand_subparam(t_data *data, char **sub_param, char *c)
{
	int		i;
	char	*new_param;
	char	*temp;
	char	**param;
	char	quote;

	new_param = ft_strdup("\0");
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

// char	*join_and_expand_subparam(t_data *data, char *param, char c)
// {
// 	char	**param_tab;
// 	int		*index_tab;
// 	char	*temp;
// 	int		i;
// 	int		j;
// 	char	*newparam;

// 	param_tab = ft_split(param_no_q, c);
// 	index_tab = locate_c(param_no_q, c);
// 	new_param = ft_strdup("\0");
// 	i = 0;
// 	j = 0;
// 	while (param_tab[i])
// 	{
// 		if (index_tab[j] == (i + j))
// 		{
// 			temp = new_param;
// 			new_param = ft_strjoin(new_param, "\'");
// 			free (temp);
// 			j++;
// 		}
// 		if (ft_strchr(param_tab[i], '$'))
// 		{
// 			temp = param_tab[i];
// 			param_tab[i] = get_and_expand(data, param_tab[i]);
// 			free (temp);
// 		}
// 		temp = new_param;
// 		new_param = ft_strjoin(new_param, param_tab[i]);
// 		free (temp);
// 		i++;
// 	}
// 	ft_del_stringtab(param_tab);
// 	free (index_tab);
// 	return (newparam);
// }

char	*double_quoted_exp(t_data *data, char *param)
{
	char	*param_no_q;
	char	**param_tab;
	char	*newparam;
	char	*temp;
	char	quote;

	param_no_q = ft_substr(param, 1, ft_strlen(param) - 2);
	free (param);
	quote = is_quoted(param_no_q);
	temp = param_no_q;
	if (quote)
	{
		param_tab = ft_split(param_no_q, '\'');
		param_no_q = join_and_expand_subparam(data, param_tab, "\'");
		ft_del_stringtab(&param_tab);
	}
	else
		param_no_q = get_and_expand(data, param_no_q);
	free (temp);
	newparam = ft_strjoin("\"", param_no_q);
	temp = newparam;
	newparam = ft_strjoin(param_no_q, "\"");
	free (temp);
	free (param_no_q);
	return (newparam);
}
