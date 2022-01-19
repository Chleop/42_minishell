/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_qualification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:36:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/19 18:44:17 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qualifiy_var(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd).nr_tok)
	{
		if (((*cmd).qualif[i] == EMPTY) && (ft_strchr((*cmd).tok[i], '$')))
			(*cmd).qualif[i] = VAR;
		i++;
	}
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
