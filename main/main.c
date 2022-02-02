/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:30 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/02 13:12:00 by avan-bre         ###   ########.fr       */
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
		if (token)
			ft_del_stringtab(&token);
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
			}
		}
		finish_up(&data);
		ft_free(&data);
	}
	free_envp(&data);
	final_exit(1, NULL);
	return (0);
}
