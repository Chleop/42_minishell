/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:54:42 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/22 17:04:36 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_io(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nr_out)
	{
		close(cmd->fd_o[i]);
		cmd->fd_o[i] = 0;
	}
	if (cmd->fd_o)
		free(cmd->fd_o);
	i = -1;
	while (++i < cmd->nr_in)
	{
		close(cmd->fd_i[i]);
		cmd->fd_i[i] = 0;
	}
	if (cmd->fd_i)
		free(cmd->fd_i);
}

void	free_envp(t_data *data)
{
	int		i;
	t_envp	*temp;

	i = -1;
	while (data->envp)
	{
		temp = data->envp;
		data->envp = data->envp->next;
		free_node_envp(temp);
	}
}

void	finish_up(t_data *data)
{
	int	i;
	int	ret;
	int	wret;

	if (data->nr_cmds > 1)
	{
		close_all_except_two(data, -1);
		i = -1;
		while (++i < data->nr_cmds)
		{
			data->pipe_fd[i][0] = 0;
			data->pipe_fd[i][1] = 0;
		}
	}
	i = -1;
	while ((++i < data->nr_pid) && data->process_id[i])
	{
		wret = waitpid(data->process_id[i], &ret, 0);
		data->process_id[i] = 0;
		if (wret >= 0 && WIFEXITED(ret))
			g_lobal.exit_code = WEXITSTATUS(ret);
	}
}

void	free_string(char **string)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
}

void	free_node_envp(t_envp *envp)
{
	if (envp)
	{
		free_string(&envp->name);
		free_string(&envp->var);
		free(envp);
		envp = NULL;
	}
}
