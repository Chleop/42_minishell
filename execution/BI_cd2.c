/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:02:58 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/01 18:49:31 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_dir(char **path, char *dir)
{
	char	*temp;

	temp = *path;
	*path = ft_strjoin(*path, "/");
	*path = ft_strjoin(*path, dir);
	free(temp);
	temp = NULL;
}

void	one_dir_up(char **path)
{
	int		i;
	char	*temp;

	temp = *path;
	i = ft_strlen(*path);
	while (i && (*path)[i] != '/')
		i--;
	*path = ft_substr(*path, 0, i);
	free(temp);
	temp = NULL;
}

int	get_level(void)
{
	char	*cwd;
	int		i;
	int		level;

	level = 0;
	cwd = getcwd(NULL, 0);
	i = -1;
	while (cwd[++i])
	{
		if (cwd[i] == '/')
			level++;
	}
	free(cwd);
	cwd = NULL;
	return (level);
}

void	change_dir(char *path, int level)
{
	if (chdir(path) == -1)
	{
		if (level < 1)
			chdir("/");
		else
			perror("error - cd");
	}
}

void	handle_dots(t_cmd *cmd)
{
	char	**dir_tab;
	char	*path;
	int		i;
	int		level;

	level = get_level();
	dir_tab = ft_split(cmd->param[1], '/');
	path = getcwd(NULL, 0);
	i = -1;
	while (dir_tab[++i])
	{
		if (ft_strncmp(dir_tab[i], "..\0",
				ft_strlen(dir_tab[i]) + 1) == 0 && level > 0)
		{
			one_dir_up(&path);
			level--;
		}
		else if (ft_strncmp(dir_tab[i], ".\0", ft_strlen(dir_tab[i]) + 1))
		{
			add_dir(&path, dir_tab[i]);
			level++;
		}
	}
	change_dir(path, level);
	free_dir_tab(dir_tab);
}
