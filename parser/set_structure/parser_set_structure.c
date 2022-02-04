/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:54:01 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/04 16:10:23 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	expand_and_classify(t_data *data, char **token, int cmd_nr, int tok_nr)
// {
// 	char	*temp;

// 	printf("token = %s\n", data->cmd[cmd_nr].tok[tok_nr]);
// 	if (ft_strchr(data->cmd[cmd_nr].tok[tok_nr], '$'))
// 	{
// 		temp = *token;
// 		*token = manage_expansions(data, temp);
// 		if (!(*token))
// 			return (0);
// 		free (temp);
// 	}
// 	else
// 	{
// 		if (!identify_remove_quotes(token))
// 			return (ft_error2("Error: malloc failed", data, 1));
// 	}
// 	if (!classify_token(data, token, cmd_nr, tok_nr))
// 		return (0);
// 	return (1);
// }

int	expand_and_classify(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	char	*temp;

	printf("token = %s\n", data->cmd[cmd_nr].tok[tok_nr]);
	if (ft_strchr(data->cmd[cmd_nr].tok[tok_nr], '$'))
	{
		temp = *token;
		*token = manage_expansions(data, temp);
		if (!(*token))
			return (0);
		free (temp);
		if (!classify_token(data, token, cmd_nr, tok_nr))
			return (0);
	}
	else
	{
		if (!classify_token(data, token, cmd_nr, tok_nr))
			return (0);
		if (!identify_remove_quotes(&(data->cmd[cmd_nr].param[tok_nr])))
			return (ft_error2("Error: malloc failed", data, 1));
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

void	expand_cmd_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!data->cmd[i].param)
			return ;
		if (!is_builtin(&(data->cmd[i])))
		{
			temp = data->cmd[i].param[0];
			data->cmd[i].param[0] = get_path(data, data->cmd[i].param[0]);
			free (temp);
			temp = NULL;
		}
		i++;
	}
}

int	set_into_structure(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nr_cmds)
	{
		j = 0;
		while (j < data->cmd[i].nr_tok)
		{
			if (!expand_and_classify(data, &(data->cmd[i].tok[j]), i, j))
				return (0);
			j++;
		}
		i++;
	}
	expand_cmd_path(data);
	return (1);
}
