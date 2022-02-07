/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd2_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:47:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/07 18:24:07 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_dir(t_cd *cd, char *dir)
{
	char	*temp;

	temp = cd->path;
	cd->path = ft_strjoin(cd->path, "/");
	free_string(temp);
	temp = cd->path;
	cd->path = ft_strjoin(cd->path, dir);
	free_string(temp);
	cd->level++;
}

void	one_dir_up(t_cd *cd)
{
	int		i;
	char	*temp;

	temp = cd->path;
	if (cd->level > 1)
	{
		i = ft_strlen(cd->path);
		while (i && (cd->path)[i] != '/')
			i--;
		cd->path = ft_substr(cd->path, 0, i);
	}
	else
		cd->path = ft_substr(cd->path, 0, 1);
	free_string(temp);
	cd->level--;
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

void	handle_dots(t_cmd *cmd, t_cd *cd)
{
	char	**dir_tab;
	int		i;
	
	cd->level = get_level(cd->oldpwd);
	cd->path = ft_strdup(cd->oldpwd);
	dir_tab = ft_split(cmd->param[1], '/');
	i = -1;
	while (dir_tab[++i])
	{
		if (!ft_strncmp(dir_tab[i], "..\0",
			ft_strlen(dir_tab[i]) + 1) && cd->level > 0)
			one_dir_up(cd);
		else if (ft_strncmp(dir_tab[i], ".\0",
			ft_strlen(dir_tab[i]) + 1) != 0)
			add_dir(cd, dir_tab[i]);
	}
	chdir_path(cmd->data, cd);
	ft_del_stringtab(&dir_tab);
}