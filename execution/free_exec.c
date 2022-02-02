/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:54:42 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/02 12:51:39 by avan-bre         ###   ########.fr       */
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
	free(cmd->fd_o);
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
		free_string(temp->name);
		free_string(temp->var);
		if (temp)
		{
			free(temp);
			temp = 0;
		}
	}
}

void	finish_up(t_data *data)
{
	int	i;

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
	while ((++i < data->nr_cmds) && data->process_id[i])
	{
		waitpid(data->process_id[i], NULL, 0);
		data->process_id[i] = 0;
	}
}

void	free_string(char *string)
{
//	printf("freeing %s\n", string);
	if (string)
	{
		free(string);
		string = NULL;
	}
}