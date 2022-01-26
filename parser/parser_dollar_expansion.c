/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/13 14:18:45 by cproesch         ###   ########.fr       */
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
	while (data->envp[i])
	{
		if (ft_strnstr(data->envp[i], param, len))
			exp = ft_substr(data->envp[i], len + 1, (ft_strlen(data->envp[i]) - len - 1));
		i++;
	}
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

void	manage_expansions(t_data *data, char **token)
{
	char	*pre;
	char	*param;
	char	*post;
	char	*free_var;
	int		par_i;
	int		post_len;

	while (ft_strchr(*token, '$'))
	{
		par_i = ft_strchr(*token, '$') - *token + 1;
		pre = (char *)ft_calloc(par_i, sizeof(char));
		if (!pre)
			perror("Error");
		ft_memcpy(pre, *token, par_i - 1);
		param = (char *)ft_calloc(ft_param_len(*token) + 1, sizeof(char));
		if (!param)
			perror("Error");
		ft_memcpy(param, *token + par_i, ft_param_len(*token));
		post_len = ft_strlen(*token) - (par_i + ft_param_len(*token));
		post = (char *)ft_calloc(post_len + 1, sizeof(char));
		if (!post)
			perror("Error");
		ft_memcpy(post, *token + par_i + ft_param_len(*token), post_len);
		free_var = *token;
		*token = replace_param_by_extansion(data, pre, param, post);
		free(free_var);
		free(pre);
		free(param);
		free(post);
	}
	return ;
}
