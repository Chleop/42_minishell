/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_step_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:55:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/21 15:08:07 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	review_operators(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if ((token[i][0] == '|') || (token[i][0] == '>')
		|| (token[i][0] == '<'))
		{
			if ((ft_strncmp(token[i], "|\0", 2)
					&& ft_strncmp(token[i], "<\0", 2)
					&& ft_strncmp(token[i], ">\0", 2)
					&& ft_strncmp(token[i], ">>\0", 3)
					&& ft_strncmp(token[i], "<<\0", 3)
					&& ft_strncmp(token[i], ">|\0", 3))
				|| (!token[i + 1])
				|| (((i - 1) > -1) && ((token[i - 1][0] == '>')
					|| (token[i - 1][0] == '<')))
					|| (((i - 1) > -1) && (token[i][0] == '|')
					&& (token[i - 1][0] == '|')))
				return (ft_error2("Syntax error", token[i], 2));
		}
		i++;
	}
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	if ((ft_strncmp(cmd->param[0], "echo\0", 5) == 0)
		|| (ft_strncmp(cmd->param[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(cmd->param[0], "env\0", 4) == 0)
		|| (ft_strncmp(cmd->param[0], "cd\0", 3) == 0)
		|| (ft_strncmp(cmd->param[0], "export\0", 7) == 0)
		|| (ft_strncmp(cmd->param[0], "unset\0", 6) == 0)
		|| (ft_strncmp(cmd->param[0], "exit\0", 5) == 0))
		return (1);
	return (0);
}

int	expand_cmd_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!data->cmd[i].param)
			return (1);
		if (!is_builtin(&(data->cmd[i])))
		{
			temp = data->cmd[i].param[0];
			data->cmd[i].param[0] = get_path(data, data->cmd[i].param[0]);
			if (!data->cmd[i].param[0])
				return (0);
			free (temp);
			temp = NULL;
		}
		i++;
	}
	return (1);
}

int	parse(t_data *data, char **token)
{
	if (!review_operators(token))
		return (0);
	if (!initialize_data(data, token))
		return (0);
	if (!initialize_cmds(data, token))
		return (0);
	if (!grammatize_tokens(data))
		return (0);
	if (!expand_and_set_into_structure(data))
		return (0);
	if (!remove_quotes_inside_struct(data))
		return (0);
	if (!expand_cmd_path(data))
		return (0);
	return (1);
}
