/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:25 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 18:10:06 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	t_envp	*temp;

	exp = ft_strdup("\0");
	temp = data->envp;
	while (temp && ft_strlen(to_be_exp))
	{
		if (!ft_strncmp(temp->name, to_be_exp, ft_strlen(temp->name) + 1))
		{
			exp = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	return (exp);
}

int	count_token(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

int	localize_pipes(t_data *data, char **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			data->parser.pipe[j] = i;
			j++;
		}
		i++;
	}
	return (j);
}
