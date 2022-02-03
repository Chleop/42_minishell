/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:19:50 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 11:31:32 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_nonbuiltins(t_cmd *cmd)
{
	if (execve(cmd->param[0], cmd->param, NULL) == -1)
	{
		ft_free_data(cmd->data);
		perror("error - execution fail");
		exit (1);
	}
	ft_free_data(cmd->data);
	exit (0);
}

int	exec_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->param[0], "echo\0", 5) == 0)
	{
		ft_echo(cmd);
		return (1);
	}
	else if (ft_strncmp(cmd->param[0], "pwd\0", 4) == 0)
	{
		ft_pwd();
		ft_free_data(cmd->data);
		return (1);
	}
	else if (ft_strncmp(cmd->param[0], "env\0", 4) == 0)
	{
		ft_env(cmd);
		return (1);
	}
	return (0);
}

int	fork_function(t_cmd *cmd)
{
	cmd->data->process_id[cmd->id] = fork();
	if (cmd->data->process_id[cmd->id] == -1)
	{
		perror("error - fork failed");
		return (-1);
	}
	else if (cmd->data->process_id[cmd->id] == 0)
	{
		if (redirect_io(cmd) == 0)
			return (-1);
		if (cmd->data->nr_cmds > 1)
			pipe_function(cmd);
		if (exec_builtins(cmd) == 1)
			return (1);
		else if (exec_nonbuiltins(cmd) == 1)
			return (2);
		else
			return (0);
	}
	return (0);
}

int	exec_prefork_builtins2(t_cmd *cmd, enum BI funct)
{
	int		current_stdin;
	int		current_stdout;

	if (funct == EXIT)
		ft_exit(cmd);
	current_stdin = dup(STDIN_FILENO);
	current_stdout = dup(STDOUT_FILENO);
	if (!redirect_io(cmd))
	{
		close(current_stdin);
		close(current_stdout);
		ft_free_data(cmd->data);
		return (-1);
	}
	if (cmd->data->nr_cmds > 1)
		pipe_function(cmd);
	if (funct == CD)
		ft_cd(cmd);
	else if (funct == EXPORT)
		ft_export(cmd);
	else if (funct == UNSET)
		ft_unset(cmd);
	reverse_redirection(cmd, current_stdin, current_stdout);
	return (1);
}

int	exec_prefork_builtins(t_cmd *cmd)
{
	enum BI	funct;

	funct = 0;
	if (ft_strncmp(cmd->param[0], "cd\0", 3) == 0)
		funct = CD;
	else if (ft_strncmp(cmd->param[0], "export\0", 7) == 0)
		funct = EXPORT;
	else if (ft_strncmp(cmd->param[0], "unset\0", 6) == 0)
		funct = UNSET;
	else if (ft_strncmp(cmd->param[0], "exit\0", 5) == 0)
		funct = EXIT;
	if (funct)
	{
		if (cmd->data->nr_cmds > 1)
			return (1);
		if (exec_prefork_builtins2(cmd, funct) == -1)
			return (-1);
		return (1);
	}
	return (0);
}
