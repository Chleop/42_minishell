/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:42:54 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 12:36:25 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_env(t_data *data)
{
	char	*path;
	t_envp	*temp;

	path = ft_strdup("\0");
	temp = data->envp;
	while (temp)
	{
		if (!ft_strncmp(temp->name, "PATH\0", 5))
		{
			path = ft_strdup(temp->var);
			break;
		}
		temp = temp->next;
	}
	return (path);
}

int	join_c(char	**tab, char	*str)
{
	int		i;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		temp = tab[i];
		tab[i] = ft_strjoin(tab[i], str);
		free(temp);
		if (!tab[i])
			return (0);
		i++;
	}
	return (1);
}

char	*find_accessible_path(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (access(tab[i], 1) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}

char	*find_path(t_data *data, char *cmd)
{
	char	*str_path_env;
	char	**tab_path_env;
	char	*path;

	if (!cmd[0])
		return (ft_strdup(cmd));
	str_path_env = find_path_env(data);
	tab_path_env = ft_split(str_path_env, ':');
	if (!tab_path_env)
		return (NULL);
	if (!(join_c(tab_path_env, "/")) || !(join_c(tab_path_env, cmd)))
		return (NULL);
	path = ft_strdup(find_accessible_path(tab_path_env));
	ft_del_stringtab(&tab_path_env);
	if ((!path) || (access(cmd, 1) == 0))
		return (ft_strdup(cmd));
	return (path);
}
