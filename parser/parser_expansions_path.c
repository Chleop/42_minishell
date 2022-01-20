/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansions_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:42:54 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/20 19:22:45 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH\0", 5))
			return (ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 4)));
		i++;
	}
	return (NULL);
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

char	*find_path(char **envp, char *cmd)
{
	char	*str_path_env;
	char	**tab_path_env;
	char	*path;

	if (!cmd[0])
		return (ft_strdup(cmd));
	str_path_env = find_path_env(envp);
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
