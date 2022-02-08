/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:30 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 17:04:45 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parser(t_data *data, int *ret)
{
	char	*input;
	char	**token;

	input = NULL;
	token = NULL;
	input = readline("our_minishell:~$ ");
	add_history(input);
	if (input)
		token = lexer(input);
	if (token)
	{
		*ret = parse(data, token);
		ft_free_parser(data, &token);
		// printf ("after syntax error, exit code= %d\n", exit_code);
	}
}

void	loop_through_commands(t_data *data)
{
	int		current_stdin;
	int		current_stdout;
	int		i;

	i = -1;
	while (++i < data->nr_cmds)
	{
		if (data->cmd[i].param == NULL)
		{
			current_stdin = dup(STDIN_FILENO);
			current_stdout = dup(STDOUT_FILENO);
			redirect_io(&data->cmd[i]);
			reverse_redirection(&data->cmd[i],
				current_stdin, current_stdout);
		}
		else if (exec_prefork_builtins(&(data->cmd[i])) == 0)
			fork_function(&data->cmd[i]);
	}
}

void	execute_commands(t_data *data, int *ret)
{
	int		status;

	if (ret)
	{
		// printf ("in main process, exit code= %d\n", exit_code);
		status = 1;
		if (data->nr_cmds > 1)
			status = init_pipes(data);
		if (status)
			loop_through_commands(data);
		finish_up(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		ret;

	if ((argc > 1) || (argv[1]))
		final_exit(&data, "Error: too many arguments");
	init_envp(&data, envp);
	while (42)
	{
		lexer_parser(&data, &ret);
		execute_commands(&data, &ret);
		ft_free_data(&data, 0);
	}
	final_exit(&data, NULL);
	return (0);
}
