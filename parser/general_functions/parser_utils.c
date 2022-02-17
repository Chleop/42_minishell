/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:25 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/17 15:50:31 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_code_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	char	*exit_char;
	char	*post;

	exit_char = ft_itoa(data->exit_code);
	post = ft_strdup(to_be_exp + 1);
	exp = ft_strjoin(exit_char, post);
	free(exit_char);
	free(post);
	return (exp);
}

char	*get_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	t_envp	*temp;

	temp = data->envp;
	exp = NULL;
	if (to_be_exp[0] == '?')
		return (exit_code_expansion(data, to_be_exp));
	while (temp && ft_strlen(to_be_exp))
	{
		if (!ft_strncmp(temp->name, to_be_exp, ft_strlen(temp->name) + 1))
		{
			exp = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	if ((!exp) && !ft_strncmp("PATH\0", to_be_exp, 5))
		exp = ft_strdup(to_be_exp);
	else if (!exp)
		exp = ft_strdup("\0");
	return (exp);
}

int	count_strings(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}
