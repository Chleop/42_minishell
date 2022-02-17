/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:30 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/17 10:40:04 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parser(t_data *data, int *ret)
{
	char	*input;
	char	**token;

	input = NULL;
	token = NULL;
	//signal_handler(data, 1);
	//my idea was to catch ctrl-c with this, saying we are in the parent (1),
	//so we want to display '^C' and then a new prompt
	input = readline(PURPLE "our_minishell:~$ " RESET);
	if (!input)
	{
		data->eof = 1;
		ft_printf("exit\n", 1);
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

void	handle(int sig)
{
	signal(sig, SIG_IGN);
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
		ret = 0;
		lexer_parser(&data, &ret);
		execute_commands(&data, &ret);
		ft_free_data(&data, 0);
	}
	final_exit(&data);
	return (0);
}
