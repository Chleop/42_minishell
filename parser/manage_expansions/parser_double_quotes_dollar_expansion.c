/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double_quotes_dollar_expansion.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:32:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/10 13:04:58 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// seperated the single quotes

char	*seperate_s_in_d_quotes(t_data *data, char *token, char c)
{
	char	**sub_param;
	int		*index_tab;
	char	*new_token;

	index_tab = locate_c_in_string(token, c);
	sub_param = ft_split(token, c);
	new_token = expand_s_in_d(data, sub_param, index_tab);
	ft_del_stringtab(&sub_param);
	free(index_tab);
	return (new_token);
}

char	*join_two_strings(char *str1, char *str2)
{
	char	*temp;

	temp = str1;
	str1 = ft_strjoin(str1, str2);
	free (temp);
	return (str1);
}

// expands dollar inside single quotes when doubes quoted

char	*expand_s_in_d(t_data *data, char **sub_param, int *index_tab)
{
	int		i;
	char	*new_param;
	char	*temp;

	new_param = ft_strdup("\0");
	i = -1;
	while (sub_param[++i])
	{
		if (((i == 0) && (index_tab[0] == 0))
			|| ((i == 1) && (index_tab[0] != 0)))
			new_param = join_two_strings(new_param, "\'");
		if (ft_strchr(sub_param[i], '$'))
		{
			temp = sub_param[i];
			sub_param[i] = manage_expansions(data, sub_param[i]);
			free (temp);
		}
		temp = new_param;
		new_param = ft_strjoin(new_param, sub_param[i]);
		free (temp);
		if (((i == 0) && (index_tab[0] == 0))
			|| ((i == 1) && (index_tab[0] != 0)))
			new_param = join_two_strings(new_param, "\'");
	}
	return (new_param);
}

// The subtoken is double quoted
// Removes the double quotes
// If the subtoken is single quoted, splits it into subsubtoken
// Expands the parameter (spliting by spaes if needed) and rejoins
// the subsubtokens
// Otherwise, splits the subtoken by spaces, expands and rejoins
// the subtokens
// Repositions the double quotes

char	*double_quoted_exp(t_data *data, char *param)
{
	char	*param_no_q;
	char	*newparam;
	char	*temp;
	char	quote;

	param_no_q = ft_substr(param, 1, ft_strlen(param) - 2);
	quote = is_quoted(param_no_q);
	temp = param_no_q;
	if (quote)
		param_no_q = seperate_s_in_d_quotes(data, param_no_q, '\'');
	else
		param_no_q = manage_expansions(data, param_no_q);
	free (temp);
	newparam = ft_strjoin("\"", param_no_q);
	temp = newparam;
	newparam = ft_strjoin(newparam, "\"");
	free (temp);
	free (param_no_q);
	return (newparam);
}
