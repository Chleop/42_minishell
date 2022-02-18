/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_step_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:54:01 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/18 13:39:50 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// In each command, takes each token and classifies it in the param 
// structure or in the file in/out tables. Finally expand_path expands 
// the command paths.

int	expand_and_set_into_structure(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nr_cmds)
	{
		j = 0;
		while (j < data->cmd[i].nr_tok)
		{
			if (data->cmd[i].qualif[j] != HERE_END
				&& ft_strchr(data->cmd[i].tok[j], '$'))
			{
				if (!manage_expansions(data, &data->cmd[i].tok[j], 0)
					|| !set_into_structure2(data, &data->cmd[i].tok[j], i, j))
					return (0);
			}
			else if (!set_into_structure1(data, &data->cmd[i].tok[j], i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
