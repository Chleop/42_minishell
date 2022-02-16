/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:19:50 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/16 16:31:21 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_nonbuiltins(t_cmd *cmd)
{
	char	**envp_tab;

	envp_tab = NULL;
	if (access(cmd->param[0], F_OK))
		ft_error2("command not found", cmd->param[0], cmd->data, 127);
	else
	{
		convert_envp(cmd->data->envp, &envp_tab);
		if (execve(cmd->param[0], cmd->param, envp_tab) == -1)
			ft_error2(strerror(errno), cmd->param[0], cmd->data, 126);
		ft_del_stringtab(&envp_tab);
	}
	final_exit(cmd->data);
}

int	exec_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->param[0], "echo\0", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->param[0], "pwd\0", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->param[0], "env\0", 4) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd->param[0], "export\0", 7) == 0)
		ft_export_fork(cmd);
	else
		return (0);
	return (1);
}

int	fork_function(t_cmd *cmd)
{
	cmd->data->process_id[cmd->id] = fork();
	if (cmd->data->process_id[cmd->id] == -1)
		return (ft_error2(strerror(errno), NULL, cmd->data, 1));
	else if (cmd->data->process_id[cmd->id] == 0)
	{
		if (!redirect_io(cmd))
			final_exit(cmd->data);
		if (cmd->data->nr_cmds > 1)
			pipe_function(cmd);
		if (!exec_builtins(cmd))
			exec_nonbuiltins(cmd);
		final_exit(cmd->data);
		return (1);
	}
	return (0);
}

int	exec_prefork_builtins2(t_cmd *cmd, enum BI funct)
{
	int		current_stdin;
	int		current_stdout;

	current_stdin = dup(STDIN_FILENO);
	current_stdout = dup(STDOUT_FILENO);
	if (!redirect_io(cmd))
	{
		close(current_stdin);
		close(current_stdout);
		ft_free_data(cmd->data, 0);
		return (0);
	}
	if (cmd->data->nr_cmds > 1)
		pipe_function(cmd);
	if (funct == CD)
		ft_cd(cmd);
	else if (funct == EXPORT)
		ft_export_prefork(cmd);
	else if (funct == UNSET)
		ft_unset(cmd);
	reverse_redirection(cmd, current_stdin, current_stdout);
	return (1);
}

int	exec_prefork_builtins(t_cmd *cmd)
{
	enum BI	funct;

	funct = 0;
	if (ft_strncmp(cmd->param[0], "exit\0", 5) == 0)
	{
		ft_exit(cmd);
		return (1);
	}
	else if (ft_strncmp(cmd->param[0], "cd\0", 3) == 0)
		funct = CD;
	else if (ft_strncmp(cmd->param[0], "export\0", 7) == 0
		&& cmd->param[1])
		funct = EXPORT;
	else if (ft_strncmp(cmd->param[0], "unset\0", 6) == 0)
		funct = UNSET;
	if (funct)
	{
		if (cmd->data->nr_cmds > 1)
			return (1);
		return (exec_prefork_builtins2(cmd, funct));
	}
	return (2);
}
