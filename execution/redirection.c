/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/01 15:54:31 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nr_in)
	{
		cmd->fd_i[i] = open(cmd->i[i], O_RDONLY);
		if (cmd->fd_i[i] == -1)
		{
			perror("error - could not open input file");
			return (-1);
		}
		if (access(cmd->i[i], R_OK) != 0)
		{
			perror("error - can not read input file");
			return (-1);
		}
	}
	if (cmd->fd_i)
		dup2(cmd->fd_i[i - 1], STDIN_FILENO);
	i = -1;
	while (++i < cmd->nr_in)
		close(cmd->fd_i[i]);
	return (1);
}

int	redirect_output(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nr_out)
	{
		if (cmd->type[i] == 1)
			cmd->fd_o[i] = open(cmd->o[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (cmd->type[i] == 2)
		 	cmd->fd_o[i] = open(cmd->o[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (cmd->fd_o[i] == -1)
		{
			perror ("error - could not open output file");
			return (0);
		}
		if (access(cmd->o[i], W_OK) != 0)
		{
			perror("error - can not write to output file");
			return (0);
		}
	}
	if (cmd->fd_o)
		dup2(cmd->fd_o[i - 1], STDOUT_FILENO);
	i = -1;
	free_io(cmd);
	while (++i < cmd->nr_out)
		close(cmd->fd_o[i]);
	return (1);
}

int	redirect_io(t_cmd *cmd)
{
	cmd->fd_o = malloc(sizeof(int) * cmd->nr_out);
	if (!cmd->fd_o)
	{
		perror("malloc failed");
		return (0);
	}
	cmd->fd_i = malloc(sizeof(int) * cmd->nr_in);
	if (!cmd->fd_i)
	{
		perror("malloc failed");
		return (0);
	}
	if (redirect_input(cmd) == 0)
		return (0);
	if (redirect_output(cmd) == 0)
		return (0);
	return (1);
}

void	reverse_redirection(t_cmd *cmd, int in, int out)
{
	if (cmd->nr_in)
		dup2(in, STDIN_FILENO);
	if (cmd->nr_out)
		dup2(out, STDOUT_FILENO);
	if (cmd->id == 0 & cmd->data->nr_cmds > 1)
		dup2(out, STDOUT_FILENO);
	else if (cmd->id == cmd->data->nr_cmds && cmd->data->nr_cmds > 1)
		dup2(in, STDIN_FILENO);
	else if (cmd->data->nr_cmds > 1)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
	}
	close(in);
	close(out);
}
