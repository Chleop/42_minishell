/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/12 16:30:06 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_param_by_extansion(t_lex *lex, char* pre_param, char *param, char *post_param)
{
	int		i;
	int		len;
	char	*expansion;
	char	*new_token;
	char	*free_var;

	i = 0;
	len = (int)ft_strlen(param);
	while (lex->envp[i])
	{
		if (ft_strnstr(lex->envp[i], param, len))
			expansion = ft_substr(lex->envp[i], len + 1, (ft_strlen(lex->envp[i]) - len));
		i++;
	}
	// printf("expansion = %s\n", expansion);
	new_token = ft_strjoin(pre_param, expansion);
	free_var = new_token;
	new_token = ft_strjoin(new_token, post_param);
	free (free_var);
	// printf("new_temp = %s\n", new_token);
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

void	manage_expansions(t_lex *lex, char ***token)
{
	char	*pre_param;
	char	*param;
	char	*post_param;
	char	*free_var;
	int		param_position;
	int		post_param_len;
	char	*last_token;

	while (ft_strchr((*token)[lex->token_nb - 1], '$'))
	{
		last_token = (*token)[lex->token_nb - 1];
		// printf("last token = %s\n", last_token);
		param_position = ft_strchr(last_token, '$') - last_token + 1;
		// printf("position du parametre = %d\n", param_position);
		// printf ("taille du param = %d\n", ft_param_len(last_token));
		pre_param = (char *)ft_calloc(param_position, sizeof(char));
		if (!pre_param)
			perror("Error");
		ft_memcpy(pre_param, last_token, param_position - 1);
		// printf("pre_param = %s\n", pre_param);
		param = (char *)ft_calloc(ft_param_len(last_token) + 1, sizeof(char));
		if (!param)
			perror("Error");
		ft_memcpy(param, last_token + param_position, ft_param_len(last_token));
		// printf("param = %s\n", param);
		post_param_len = ft_strlen(last_token) - (param_position + ft_param_len(last_token));
		// printf("post_param_len = %d\n", post_param_len);
		post_param = (char *)ft_calloc(post_param_len + 1, sizeof(char));
		if (!post_param)
			perror("Error");
		ft_memcpy(post_param, last_token + param_position + ft_param_len(last_token), post_param_len);
		// printf("post_param = %s\n", post_param);
		free_var = (*token)[lex->token_nb - 1];
		(*token)[lex->token_nb - 1] = replace_param_by_extansion(lex, pre_param, param, post_param);
		free(free_var);
		free(pre_param);
		free(param);
		free(post_param);
	}
	return ;
}
