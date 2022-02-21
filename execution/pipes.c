/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:03:37 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 15:02:57 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_except(t_data *data, int pipe, int index)
{
	int	i;

	i = -1;
	while (++i < (data->nr_cmds - 1))
	{
		if (i != pipe)
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
		}
		else
		{
			if (index == 0)
				close(data->pipe_fd[i][1]);
			else
				close(data->pipe_fd[i][0]);
		}
	}
}

void	close_all_except_two(t_data *data, int pipe)
{
	int	i;

	i = 0;
	while (i < (data->nr_cmds - 1))
	{
		if (i == pipe)
		{
			close(data->pipe_fd[i][1]);
			i++;
			close(data->pipe_fd[i][0]);
		}
		else
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
		}
		i++;
	}
}

void	pipe_function(t_cmd *cmd)
{
	if (cmd->id == 0)
	{
		close_all_except(cmd->data, 0, 1);
		if (!cmd->nr_out)
			dup2(cmd->data->pipe_fd[0][1], STDOUT_FILENO);
		close(cmd->data->pipe_fd[0][1]);
	}
	else if (cmd->id == (cmd->data->nr_cmds - 1))
	{
		close_all_except(cmd->data, cmd->id - 1, 0);
		if (!cmd->nr_in)
			dup2(cmd->data->pipe_fd[cmd->id - 1][0], STDIN_FILENO);
		close(cmd->data->pipe_fd[cmd->id - 1][0]);
	}
	else
	{
		close_all_except_two(cmd->data, cmd->id - 1);
		if (!cmd->nr_in)
			dup2(cmd->data->pipe_fd[cmd->id - 1][0], STDIN_FILENO);
		if (!cmd->nr_out)
			dup2(cmd->data->pipe_fd[cmd->id][1], STDOUT_FILENO);
		close(cmd->data->pipe_fd[cmd->id - 1][0]);
		close(cmd->data->pipe_fd[cmd->id][1]);
	}
}

int	init_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (data->nr_cmds - 1))
		if (pipe(data->pipe_fd[i]) == -1)
			return (ft_error2(strerror(errno), NULL, 1));
	return (1);
}
