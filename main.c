/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:30 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 18:28:28 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**token;
	t_data	data;
	int		ret;
	int		status;
	int		i;

	if ((argc > 1) || (argv[1]))
		final_exit(127, "Error: too many arguments");
	init_envp(&data, envp);
	input = NULL;
	token = NULL;
	while (42)
	{
		input = readline("our_minishell:~$ ");
		add_history(input);
		if (input)
			token = lexer(input);
		if (token)
			ret = parse(&data, token);
		if (ret)
		{
			status = 1;
			if (data.nr_cmds > 1)
				status = init_pipes(&data);
			if (status)
			{
				i = -1;
				while (++i < data.nr_cmds)
				{
					if (!exec_prefork_builtins(&(data.cmd[i])))
						fork_function(&data.cmd[i]);
					// not sure to protect with if -1, exit
				}
			}
			finish_up(&data);
			ft_free(&data, token);
		}
	}
	final_exit(1, NULL);
	return (0);
}
