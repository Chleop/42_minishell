/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:42:54 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/18 11:58:00 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*exit_code_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	char	*exit_char;
	char	*post;

	exit_char = ft_itoa(data->exit_code);
	post = ft_strdup(to_be_exp + 1);
	exp = ft_strjoin(exit_char, post);
	free(exit_char);
	free(post);
	return (exp);
}

char	*get_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	t_envp	*temp;

	temp = data->envp;
	exp = NULL;
	if (to_be_exp[0] == '?')
		return (exit_code_expansion(data, to_be_exp));
	while (temp && ft_strlen(to_be_exp))
	{
		if (!ft_strncmp(temp->name, to_be_exp, ft_strlen(temp->name) + 1))
		{
			exp = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	if ((!exp) && !ft_strncmp("PATH\0", to_be_exp, 5))
		exp = ft_strdup(to_be_exp);
	else if (!exp)
		exp = ft_strdup("\0");
	return (exp);
}

char	*get_path(t_data *data, char *cmd)
{
	char	*str_path_env;
	char	**tab_path_env;
	char	*path;

	path = NULL;
	if (!cmd[0])
		return (ft_strdup(cmd));
	str_path_env = get_expansion(data, "PATH\0");
	tab_path_env = ft_split(str_path_env, ':');
	free(str_path_env);
	if (!tab_path_env)
		return (NULL);
	if (!(join_c(tab_path_env, "/")) || !(join_c(tab_path_env, cmd)))
		return (NULL);
	path = ft_strdup(find_accessible_path(tab_path_env));
	ft_del_stringtab(&tab_path_env);
	if ((!path) || (access(cmd, F_OK) == 0))
	{
		free_string(&path);
		return (ft_strdup(cmd));
	}
	return (path);
}
