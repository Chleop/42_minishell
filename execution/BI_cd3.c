/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:35:11 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/09 13:42:55 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_curpath(char *string)
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
		curpath = ft_calloc(j + 1, sizeof(char));
	return (curpath);
}

char	*set_curpath(char *string)
{
	int		i;
	int		j;
	char	*curpath;

	i = 0;
	j = 0;
	curpath = malloc_curpath(string);
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
		curpath = ft_strdup("/");
	return (curpath);
}

int	init_cd(t_cmd *cmd, t_cd **cd)
{
	if (cmd->param[1] && cmd->param[2])
	{
		return (ft_error2("cd: too many arguments", NULL, 1));
		// ft_printf("%s\n", 2, "cd: too many arguments");
		// //exit_code is 1
		// return (0);
	}
	*cd = malloc(sizeof(t_cd) * 1);
	if (!*cd)
		return (ft_error2(strerror(errno), "cd structure", 1));
	(*cd)->oldpwd = get_var(cmd->data->envp, "PWD");
	(*cd)->current = getcwd(NULL, 0);
	(*cd)->path = NULL;
	return (1);
}
