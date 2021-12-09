/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:24:39 by cproesch          #+#    #+#             */
/*   Updated: 2021/12/09 12:30:42 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child0_process(t_data *data, char **argv, char **envp)
{
	close(data->pipefd[0][0]);
	data->input = open_read(argv[0]);
	if (data->input == -1)
		ft_exit(&data, 2);
	dup2(data->input, STDIN_FILENO);
	close(data->input);
	dup2(data->pipefd[0][1], STDOUT_FILENO);
	close(data->pipefd[0][1]);
	exec_command(data, envp, argv[1], 0);
}

void	childx_process(t_data *data, char **argv, char **envp, int x)
{
	close(data->pipefd[x - 1][1]);
	close(data->pipefd[x][0]);
	dup2(data->pipefd[x - 1][0], STDIN_FILENO);
	close(data->pipefd[x - 1][0]);
	dup2(data->pipefd[x][1], STDOUT_FILENO);
	close(data->pipefd[x][1]);
	exec_command(data, envp, argv[x + 1], x);
}

void	childn_process(t_data *data, char **argv, char **envp, int x)
{
	close(data->pipefd[x - 1][1]);
	dup2(data->pipefd[x - 1][0], STDIN_FILENO);
	close(data->pipefd[x - 1][0]);
	data->output = open_write(argv[x + 2]);
	if (data->output == -1)
		return ;
	dup2(data->output, STDOUT_FILENO);
	close(data->output);
	exec_command(data, envp, argv[x + 1], x);
}
