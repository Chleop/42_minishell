/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:24 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/11 18:26:02 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_param_by_extansion(char **envp, char *param, char *temp)
{
	int		i;
	int		len;
	char	*expansion;
	char	*new_temp;

	i = 0;
	len = (int)ft_strlen(param);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], param, len))
			expansion = ft_substr(envp[i], len + 1, (ft_strlen(envp[i]) - len));
		i++;
	}
	printf("expansion = %s\n", expansion);
	new_temp = ft_strjoin(expansion, ft_substr(temp, len + 1, (ft_strlen(temp) - len)));
	printf("new_temp = %s\n", new_temp);
	// exit(1);
	return (new_temp);
}

void	manage_expansions(t_lex *lex, char ***token, char *last_token)
{
	// int	i;
	char	*temp;
	char	*param;
	char	*free_var;

	temp = (char *)ft_calloc(lex->tok_char_nb + 1, sizeof(char));
	ft_memcpy(temp, last_token, lex->tok_char_nb);
	if (!temp)
		perror("Error");
	// printf ("taille du param = %ld\n", (ft_strchr(temp, '\0') - temp) - 1);
	param = ft_substr(temp, 1, (ft_strchr(temp, '\0') - temp) - 1);
	// printf("param = %s\n", param);
	free_var = temp;
	temp = replace_param_by_extansion(lex->envp, param, temp);
	free(free_var);

	free(param);
	free_var = (*token)[lex->token_nb - 1];
	(*token)[lex->token_nb - 1] = temp;
	free(free_var);



	// split_into_token(temp, lex->envp);

}
