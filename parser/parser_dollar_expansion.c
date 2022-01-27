/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/27 18:26:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_param_by_extansion(t_data *data, char* pre, char *param, char *post)
{
	int		i;
	int		len;
	char	*exp;
	char	*new_token;
	char	*free_var;

	i = 0;
	len = (int)ft_strlen(param);
	exp = NULL;
	while (data->envp[i])
	{
		if (ft_strnstr(data->envp[i], param, len))
			exp = ft_substr(data->envp[i], len + 1, (ft_strlen(data->envp[i]) - len - 1));
		i++;
	}
	if (!exp)
		return(ft_strjoin(pre, post));
	new_token = ft_strjoin(pre, exp);
	free_var = new_token;
	new_token = ft_strjoin(new_token, post);
	free (free_var);
	return (new_token);
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

// char	*get_sub_tok(char **token)
// {
// 	char	*pre;
// 	int		start;
// 	int		end;

// 	start = 0;
// 	while ((((*token)[pre_end]) != '\0') && (((*token)[pre_end]) != '\'')
// 	&& (((*token)[pre_end]) != '\"') && (((*token)[pre_end]) != '$'))
// 		pre_end++;
// 	pre = (char *)ft_calloc(pre_end + 1, sizeof(char));
// 	if (!pre)
// 		return (NULL);
// 	ft_memcpy(pre, *token, pre_end);
// 	return (pre);
// }

char	*manage_expansions(char *token)
{
	int		i;
	int		start;
	int		end;
	char	*sub_tok;
	char	*new_token;
	char	*temp;

	i = 0;
	new_token = ft_strdup("\0");
	while (((token)[i]) != '\0')
	{
		start = i;
		if (((token[i] == '\'') || (token[i] == '\"'))
		&& is_paired(token[i], token, i + 1))
			end = is_paired(token[i], token, i + 1);
		else
		{
			i++;
			while ((((token)[i]) != '\0') && (((token)[i]) != '\'')
			&& (((token)[i]) != '\"') && (((token)[i]) != '$'))
				i++;
			end = i;
		}
		printf ("start = %d, end = %d\n", start, end);
		sub_tok = ft_substr(token, start, end - start);
		if (!sub_tok)
			return (NULL);
		printf("subtok = [%s]\n", sub_tok);
		temp = new_token;
		new_token = ft_strjoin(temp, sub_tok);
		free(temp);
		free(sub_tok);
		printf("new_token = [%s]\n", new_token);
		exit(1);
		i++;
	}
	return (new_token);
}

// void	manage_expansions(t_data *data, char **token)
// {
// 	char	*pre;
// 	char	*param;
// 	char	*post;
// 	char	*free_var;
// 	int		par_i;
// 	int		post_len;

// 	printf("*token = [%s] with size %lu\n", *token, ft_strlen(*token));
// 	while (ft_strchr(*token, '$'))
// 	{
// 		par_i = ft_strchr(*token, '$') - *token + 1;
// 		pre = (char *)ft_calloc(par_i, sizeof(char));
// 		if (!pre)
// 			perror("Error");
// 		ft_memcpy(pre, *token, par_i - 1);
// 		param = (char *)ft_calloc(ft_param_len(*token) + 1, sizeof(char));
// 		if (!param)
// 			perror("Error");
// 		ft_memcpy(param, *token + par_i, ft_param_len(*token));
// 		post_len = ft_strlen(*token) - (par_i + ft_param_len(*token));
// 		post = (char *)ft_calloc(post_len + 1, sizeof(char));
// 		if (!post)
// 			perror("Error");
// 		ft_memcpy(post, *token + par_i + ft_param_len(*token), post_len);
// 		free_var = *token;
// 		printf ("pre = [%s], param = [%s], post = [%s]\n", pre, param, post);
// 		*token = replace_param_by_extansion(data, pre, param, post);
// 		free(free_var);
// 		free(pre);
// 		free(param);
// 		free(post);
// 	}
// 	return ;
// }
