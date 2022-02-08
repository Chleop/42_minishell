/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:23:36 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 13:24:11 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_stringtab(char ***tab)
{
	int	i;

	i = 0;
	if (!*tab)
		return ;
	while ((*tab)[i])
	{
		if ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	ft_free_parser(t_data *data, char ***token)
{
	int	i;

	i = 0;
	if (*token)
		ft_del_stringtab(token);
	if (data->cmd)
	{
		while (i < data->nr_cmds)
		{
			if (data->cmd[i].tok)
				ft_del_stringtab(&(data->cmd[i].tok));
			if (data->cmd[i].qualif)
				free(data->cmd[i].qualif);
			i++;
		}
	}
	if (data->pipe_index)
		free(data->pipe_index);
}

void	ft_free_data(t_data *data, int code)
{
	int	i;

	i = 0;
	if (code)
		free_envp(data);
	if (data->cmd)
	{
		while (i < data->nr_cmds)
		{
			if (data->cmd[i].param)
				ft_del_stringtab(&(data->cmd[i].param));
			i++;
		}
		free (data->cmd);
		data->cmd = NULL;
	}
}
