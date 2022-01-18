/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:25 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/18 18:03:43 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
