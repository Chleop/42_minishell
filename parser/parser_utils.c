/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:25 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/17 11:53:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_token(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	printf ("nb token = %d\n", i);
	return (i);
}

int	count_pipes(t_data *data, char **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			if ((i == 0) || (i == (data->nr_token - 1)))
				perror("Syntax error");
			else
				j++;
		}
		i++;
	}
	return (j);
}

