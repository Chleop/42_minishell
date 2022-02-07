/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:02:58 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/07 18:30:49 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_level(char *oldpwd)
{
	int		i;
	int		level;

	level = 0;
	i = -1;
	while (oldpwd[++i])
	{
		if (oldpwd[i] == '/')
			level++;
	}
	return (level);
}

void	add_dir(char **path, char *dir)
{
	char	*temp;

	temp = *path;
	*path = ft_strjoin(*path, "/");
	free_string(temp);
	temp = *path;
	*path = ft_strjoin(*path, dir);
	free_string(temp);
}

void	one_dir_up(char **path)
{
	int		i;
	char	*temp;

	temp = *path;
	if (get_level(*path) > 1)
	{
		i = ft_strlen(*path);
		while (i && (*path)[i] != '/')
			i--;
		*path = ft_substr(*path, 0, i);
	}
	else
		*path = ft_substr(*path, 0, 1);
	free_string(temp);
}

void	create_path(char **dir_tab, char **path, int *level)
{
	int		i;

	i = -1;
	while (dir_tab[++i])
	{
		if (!ft_strncmp(dir_tab[i], "..\0",
				ft_strlen(dir_tab[i]) + 1) && level > 0)
		{
			one_dir_up(path);
			(*level)--;
		}
		else if (ft_strncmp(dir_tab[i], ".\0", ft_strlen(dir_tab[i]) + 1))
		{
			add_dir(path, dir_tab[i]);
			(*level)++;
		}
	}
}

char	*handle_dots(t_cmd *cmd, char *oldpwd)
{
	char	**dir_tab;
	char	*path;
	int		level;

	cd->level = get_level(oldpwd);
	dir_tab = ft_split(cmd->param[1], '/');
	path = ft_strdup(oldpwd);
	//printf("Dir tab %s\nPath %s\nlevel %d\n", dir_tab[0], path, level);
	create_path(dir_tab, &path, &level);
	//printf("Path is: %s\n", path);
	if (chdir(path) == -1)
	{
		perror("error - cd");
		exit_error_cd(dir_tab, oldpwd, path);
		return (NULL);
	}
	ft_del_stringtab(&dir_tab);
	return (path);
}
