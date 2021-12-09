/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:12:26 by cproesch          #+#    #+#             */
/*   Updated: 2021/12/09 12:30:46 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("error - open file1 failed");
	return (fd);
}

int	open_write(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror("error - open file2 failed");
	return (fd);
}

char	**parse_cmd(char *argv)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(argv, ' ');
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	tab[i] = NULL;
	if (!tab)
		perror("cmd path error");
	return (tab);
}

void	exec_command(t_data *data, char **envp, char *cmd, int x)
{
	(data->cmd)[x] = parse_cmd(cmd);
	(data->cmd_path)[x] = find_path(envp, (data->cmd)[x][0]);
	if (!(data->cmd)[x] || !((data->cmd_path)[x]))
		ft_exit(&data, 2);
	if (execve((data->cmd_path)[x], (data->cmd)[x], envp) == -1)
		perror("error - First exceve failed");
}
