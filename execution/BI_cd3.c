/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:35:11 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/10 13:11:24 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_curpath(t_data *data, char *string)
{
	int		i;
	int		j;
	char	*curpath;

	i = 0;
	j = 0;
	curpath = NULL;
	while (string[i] != '\0')
	{
		if (string[i] != '/' || (string[i] == '/'
				&& !(string[i + 1] == '/' || string[i + 1] == '\0')))
			j++;
		i++;
	}
	if (j)
	{
		curpath = ft_calloc(j + 1, sizeof(char));
		if (!curpath)
			ft_error2("malloc failed", NULL, data, 1);
	}
	return (curpath);
}

void	set_curpath(t_data *data, t_cd *cd, char *string)
{
	int		i;
	int		j;
	char	*curpath;

	i = 0;
	j = 0;
	curpath = malloc_curpath(data, string);
	while (string[i])
	{
		if (string[i] != '/' || (string[i] == '/'
				&& !(string[i + 1] == '/' || string[i + 1] == '\0')))
		{
			curpath[j] = string[i];
			j++;
		}
		i++;
	}
	if (!j)
	{
		free_string(&curpath);
		curpath = ft_strdup("/");
	}
	cd->path = curpath;
}

int	init_cd(t_cmd *cmd, t_cd **cd)
{
	if (cmd->param[1] && cmd->param[2])
		return (ft_error2("cd: too many arguments", NULL, cmd->data, 1));
	*cd = malloc(sizeof(t_cd) * 1);
	if (!*cd)
		return (ft_error2(strerror(errno), NULL, cmd->data, 1));
	(*cd)->oldpwd = get_var(cmd->data->envp, "PWD");
	(*cd)->current = getcwd(NULL, 0);
	(*cd)->path = NULL;
	return (1);
}

void	free_cd(t_cd **cd)
{
	free_string(&(*cd)->oldpwd);
	free_string(&(*cd)->current);
	free_string(&(*cd)->path);
	if (*cd)
	{
		free(*cd);
		*cd = NULL;
	}
}
