/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:18:18 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/21 15:11:06 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_grammar(t_cmd *cmd)
{
	int	i;

	(*cmd).qualif = (int *)ft_calloc((*cmd).nr_tok + 1, sizeof(int));
	if (!(*cmd).qualif)
		return (ft_error("Error: malloc failed"));
	i = 0;
	while (i < (*cmd).nr_tok)
	{
		(*cmd).qualif[i] = EMPTY;
		i++;
	}
	return (1);
}

void	set_red_qualification(t_cmd *cmd, int *i, int qualif)
{
	(*cmd).qualif[*i] = OPERATOR;
	*i = *i + 1;
	(*cmd).qualif[*i] = qualif;
}

void	qualifiy_red(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd).nr_tok)
	{
		if ((*cmd).qualif[i] == EMPTY)
		{
			if (!ft_strncmp((*cmd).tok[i], ">\0", 2)
			|| !ft_strncmp((*cmd).tok[i], ">|\0", 3))
				set_red_qualification(cmd, &i, RED_OUT_S);
			else if (!ft_strncmp((*cmd).tok[i], ">>\0", 3))
				set_red_qualification(cmd, &i, RED_OUT_D);
			else if (!ft_strncmp((*cmd).tok[i], "<\0", 2))
				set_red_qualification(cmd, &i, RED_IN);
			else if (!ft_strncmp((*cmd).tok[i], "<<\0", 3))
				set_red_qualification(cmd, &i, HERE_END);
		}
		i++;
	}
}

void	qualify_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd).nr_tok)
	{
		if ((*cmd).qualif[i] == EMPTY)
		{
			(*cmd).qualif[i] = CMD;
			break;
		}
		i++;
	}
	while (i < (*cmd).nr_tok)
	{
		if ((*cmd).qualif[i] == EMPTY)
			(*cmd).qualif[i] = PARAM;
		i++;
	}
}

int	grammatize_cmds(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!initialize_grammar(&(data->cmd[i])))
			return (0);
		qualifiy_red(&(data->cmd[i]));
		qualify_cmds(&(data->cmd[i]));
		i++;
	}
	return (1);
}
