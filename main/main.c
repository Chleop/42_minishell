/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:30 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/14 13:32:34 by avan-bre         ###   ########.fr       */
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
	if (!input)
	{
		data->eof = 1;
		return ;
	}
	add_history(input);
	if (input)
		token = lexer(input);
	if (token)
	{
		*ret = parse(data, token);
		ft_free_parser(data, &token);
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
			if (redirect_io(&data->cmd[i]))
				reverse_redirection(&data->cmd[i],
					current_stdin, current_stdout);
		}
		else if (exec_prefork_builtins(&(data->cmd[i])) == 2)
			fork_function(&data->cmd[i]);
	}
}

void	execute_commands(t_data *data, int *ret)
{
	int		status;

	if (!data->eof && *ret)
	{
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

	data.exit_code = 0;
	data.eof = 0;
	data.here_doc = NULL;
	if ((argc > 1) || (argv[1]))
	{
		ft_error2("Error: too many arguments", NULL, &data, 127);
		final_exit(&data);
	}
	signal_handler(1);
	data.envp = NULL;
	init_envp(&data, envp);
	while (!data.eof)
	{	
		lexer_parser(&data, &ret);
		execute_commands(&data, &ret);
		ft_free_data(&data, 0);
	}
	final_exit(&data);
	return (0);
}
