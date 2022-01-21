/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/21 15:28:05 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_one_command(char **envp, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < (*cmd).nr_tok)
	{
		if ((*cmd).qualif[i] == CMD)
		{
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

int	expand_commands(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!expand_one_command(data->envp, &(data->cmd[i])))
			return (0);
		i++;
	}
	return (1);
}

// void	qualifiy_var(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < (*cmd).nr_tok)
// 	{
// 		if (((*cmd).qualif[i] == EMPTY) && (ft_strchr((*cmd).tok[i], '$')))
// 			(*cmd).qualif[i] = VAR;
// 		i++;
// 	}
// }

// int	expand_one_word(char **envp, t_cmd *cmd)
// {
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	while (i < (*cmd).nr_tok)
// 	{
// 		// if (c'est un dollar)
// 		{
// 			if (!identify_remove_quotes(&((*cmd).tok[i])))
// 				return (0);
// 			temp = (*cmd).tok[i];
// 			(*cmd).tok[i] = find_path(envp, (*cmd).tok[i]);
// 			if (!(*cmd).tok[i])
// 				return (ft_error("Error: malloc failed"));
// 			free (temp);
// 			temp = NULL;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (1);
// }





// int	expand_variables(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (i < data->nr_cmds)
// 	{
// 		if (!expand_one_word(data->envp, &(data->cmd[i])))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
