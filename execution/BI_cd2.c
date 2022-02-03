/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:02:58 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 15:45:17 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i = ft_strlen(*path);
	while (i && (*path)[i] != '/')
		i--;
	*path = ft_substr(*path, 0, i);
	free_string(temp);
}

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

char	*handle_dots(t_cmd *cmd, char *oldpwd)
{
	char	**dir_tab;
	char	*path;
	int		i;
	int		level;

	level = get_level(oldpwd);
	dir_tab = ft_split(cmd->param[1], '/');
	path = ft_strdup(oldpwd);
	i = -1;
	while (dir_tab[++i])
	{
		if (!ft_strncmp(dir_tab[i], "..\0",
				ft_strlen(dir_tab[i]) + 1) && level > 0)
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
	if (chdir(path) == -1)
	{
		perror("error - cd");
		return (NULL);
	}
	//change_dir(path, level);
	ft_del_stringtab(&dir_tab);
	return (path);
}
