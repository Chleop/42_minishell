/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/20 17:40:03 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_commands(char **envp, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < (*cmd).nr_tok)
	{
		if ((*cmd).qualif[i] == CMD)
		{
			if (!remove_quotes(&((*cmd).tok[i])))
				return (0);
			temp = (*cmd).tok[i];
			(*cmd).tok[i] = find_path(envp, (*cmd).tok[i]);
			if (!(*cmd).tok[i])
				return (ft_error("Error: malloc failed"));
			free (temp);
			temp = NULL;
			return (1);
		}
		i++;
	}
	return (1);
}

int	apply_expansions(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!expand_commands(data->envp, &(data->cmd[i])))
			return (0);
	// expand_files(&(data->cmd[i]));
	// expand_variables(&(data->cmd[i]));
		i++;
	}
	return (1);
}
