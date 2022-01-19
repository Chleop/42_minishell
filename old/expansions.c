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


// D'apres https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html#tag_18_09_01
// l'extansion se fait apres le parsing en simple et compound commands

// void	manage_quotes(t_lex *lex, char ***token)
// {

// }

	// i = 0;
	// while (i < lex->token_nb)
	// {
	// 	if (ft_strchr(token[i], '$'))
	// 	{
	// 		while (ft_strchr(token[i], '$'))
	// 			manage_expansions(lex, &(token[i]));
	// 	}
	// 	// else if ((ft_strchr(token[i], '\'') || (ft_strchr(token[i], '\"'))) && if ((is_paired(c, lex->input, lex->i))))
	// 	// i++;
	// }

char	*replace_param_by_extansion(t_lex *lex, char* pre_param, char *param, char *post_param)
{
	int		i;
	int		len;
	char	*expansion;
	char	*new_token;
	char	*free_var;

	i = 0;
	len = (int)ft_strlen(param);
	expansion = "\0";
	while (lex->envp[i])
	{
		if (ft_strnstr(lex->envp[i], param, len))
			expansion = ft_substr(lex->envp[i], len + 1, (ft_strlen(lex->envp[i]) - len));
		i++;
	}
	// printf("expansion = %s\n", expansion);
	new_token = ft_strjoin(pre_param, expansion);
	printf("new_temp = %s\n", new_token);
	free_var = new_token;
	new_token = ft_strjoin(new_token, post_param);
	free (free_var);
	printf("new_temp = %s\n", new_token);
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

// void	manage_expansions(t_lex *lex, char **token)
// {
// 	char	*pre_param;
// 	char	*param;
// 	char	*post_param;
// 	char	*free_var;
// 	int		param_position;
// 	int		post_param_len;
// 	int		i;

// 	while ((*token)[i])
// 	{

// 		i++;
// 	}

// 	free_var = (*token)[lex->token_nb - 1];
// 	(*token)[lex->token_nb - 1] = replace_param_by_extansion(lex, pre_param, param, post_param);
// 	free(free_var);


// 	return ;
// }

void	manage_expansions(t_lex *lex, char **token)
{
	char	*pre_param;
	char	*param;
	char	*post_param;
	char	*free_var;
	int		param_position;
	int		post_param_len;

	while (ft_strchr(*token, '$'))
	{
		param_position = ft_strchr(*token, '$') - *token + 1;
		// printf("position du parametre = %d\n", param_position);
		// printf ("taille du param = %d\n", ft_param_len(*token));
		pre_param = (char *)ft_calloc(param_position, sizeof(char));
		if (!pre_param)
			perror("Error");
		ft_memcpy(pre_param, *token, param_position - 1);
		// printf("pre_param = %s\n", pre_param);
		param = (char *)ft_calloc(ft_param_len(*token) + 1, sizeof(char));
		if (!param)
			perror("Error");
		ft_memcpy(param, *token + param_position, ft_param_len(*token));
		// printf("param = %s\n", param);
		post_param_len = ft_strlen(*token) - (param_position + ft_param_len(*token));
		// printf("post_param_len = %d\n", post_param_len);
		post_param = (char *)ft_calloc(post_param_len + 1, sizeof(char));
		if (!post_param)
			perror("Error");
		ft_memcpy(post_param, *token + param_position + ft_param_len(*token), post_param_len);
		// printf("post_param = %s\n", post_param);
		free_var = *token;
		*token = replace_param_by_extansion(lex, pre_param, param, post_param);
		free(free_var);
		free(pre_param);
		free(param);
		free(post_param);
	}
	return ;
}
