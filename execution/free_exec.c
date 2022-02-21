/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:54:42 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 13:29:36 by cproesch         ###   ########.fr       */
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
		waitpid(data->process_id[i], &ret, 0);
		data->process_id[i] = 0;
		if (WIFEXITED(ret))
			global.exit_code = WEXITSTATUS(ret);
		// else if (WIFSIGNALED(ret))
		// {
		// 	printf("WTERMSIG = %d\n", WTERMSIG(ret));
		// 	// data->exit_code = 130;
		// 	// printf("oui\n");
		// }
		data->process_id[i] = 0;
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
