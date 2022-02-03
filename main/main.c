/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:30 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/03 18:25:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**token;
	t_data	data;
	int		ret;
	int		status;
	int		i;
	int		current_stdin;
	int		current_stdout;

	if ((argc > 1) || (argv[1]))
	// {
		// exit_code = 127;
		final_exit(&data, "Error: too many arguments");
	// }
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
		{
			ret = parse(&data, token);
			ft_free_parser(&data, &token);
			// printf ("after syntax error, exit code= %d\n", exit_code);
		}
		if (ret)
		{
			// printf ("in main process, exit code= %d\n", exit_code);
			status = 1;
			if (data.nr_cmds > 1)
				status = init_pipes(&data);
			if (status)
			{
				i = -1;
				while (++i < data.nr_cmds)
				{
					if (data.cmd[i].param == NULL)
					{
						current_stdin = dup(STDIN_FILENO);
						current_stdout = dup(STDOUT_FILENO);
						redirect_io(&data.cmd[i]);
						reverse_redirection(&data.cmd[i], current_stdin, current_stdout);
					}
					else if (exec_prefork_builtins(&(data.cmd[i])) == 0)
						fork_function(&data.cmd[i]);
					// not sure to protect with if -1, exit
				}
			}
			finish_up(&data);
			
		}
		ft_free_data(&data, 0);
	}
	final_exit(&data, NULL);
	return (0);
}
