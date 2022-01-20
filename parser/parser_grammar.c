/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:18:18 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/20 15:28:07 by cproesch         ###   ########.fr       */
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

int	grammatize_tokens(t_cmd	*cmd)
{
	if (!initialize_grammar(cmd))
		return (0);
	qualifiy_var(cmd);
	qualifiy_red(cmd);
	qualify_cmds(cmd);
	return (1);
}

int	grammatize_cmds(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!grammatize_tokens(&(data->cmd[i])))
			return (0);
		i++;
	}
	return (1);
}