/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:59:40 by cproesch          #+#    #+#             */
/*   Updated: 2021/12/09 12:49:03 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_process0(t_data *data, char **argv, char **envp)
{
	(data->child)[0] = fork();
	if ((data->child)[0] == -1)
		error_message("error - First fork function failed", NULL);
	if ((data->child)[0] == 0)
		child0_process(data, argv, envp);
}

void	create_processx(t_data *data, char **argv, char **envp, int x)
{
	(data->child)[x] = fork();
	if ((data->child)[x] == -1)
		error_message("error - Fork function failed", NULL);
	if ((data->child)[x] == 0)
		childx_process(data, argv, envp, x);
	close(data->pipefd[x - 1][0]);
	close(data->pipefd[x - 1][1]);
}

void	create_processn(t_data *data, char **argv, char **envp, int x)
{
	(data->child)[x] = fork();
	if ((data->child)[x] == -1)
		error_message("error - Last fork function failed", NULL);
	if ((data->child)[x] == 0)
		childn_process(data, argv, envp, x);
	close(data->pipefd[x - 1][0]);
	close(data->pipefd[x - 1][1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		x;
	char	*str;
	char	**token;

	if (argc > 1)
		error_message("Error: too many arguments", NULL);
	if (ft_strncmp(argv[0], "./minishell", 11))
		error_message("Error: ", NULL);
	while (42)
	{
		ft_putstr_fd("minishou:~$ ", 1);
		str = get_next_line (0);
		token = ft_split(str, ' ');
		free (str);
		data = (t_data *)ft_calloc(1, sizeof(t_data));
		if (!data)
			error_message("error - Data malloc failed", NULL);
		x = 0;
		while (token[x])
			x++;
		data->max_cmd = x - 2;
		x = -1;
		while (++x < (data->max_cmd - 1))
		{
			if (pipe((data->pipefd)[x]) == -1)
				error_message("error - Pipe function failed", NULL);
		}
		create_process0(data, token, envp);
		x = 0;
		while (++x < (data->max_cmd - 1))
			create_processx(data, token, envp, x);
		create_processn(data, token, envp, x);
		x = -1;
		while (++x < data->max_cmd)
			waitpid((data->child)[x], NULL, 0);
		ft_exit(&data, 0);
	}
	return (0);
}
