/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/23 11:56:41 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = get_var(cmd->data->envp, "PWD");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	ft_printf("%s\n", 1, pwd);
	free_string(&pwd);
	g_lobal.exit_code = 0;
}

void	no_backslash(char *param, int *j)
{
	int	i;

	i = 1;
	while (param[i] == 'n')
		i++;
	if (param[i] != '\0')
		return ;
	else
		(*j)++;
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	if (cmd->param[1] == NULL)
	{
		ft_printf("\n", 1);
		g_lobal.exit_code = 0;
		return ;
	}
	i = 0;
	j = 0;
	while (cmd->param[++i] && !(ft_strncmp(cmd->param[i], "-n", 2)))
		no_backslash(cmd->param[i], &j);
	i = j;
	while (cmd->param[++i] && cmd->param[i + 1])
		ft_printf("%s ", 1, cmd->param[i]);
	if (j && cmd->param[i])
		ft_printf("%s", 1, cmd->param[i]);
	else if (j)
		ft_printf("", 1);
	else
		ft_printf("%s\n", 1, cmd->param[i]);
	g_lobal.exit_code = 0;
}

void	ft_env(t_cmd *cmd)
{
	char	*path;
	t_envp	*temp;

	temp = cmd->data->envp;
	path = get_expansion(cmd->data, "PATH");
	if (cmd->param[1] != NULL)
		ft_error2("env: too many arguments", NULL, 127);
	else if (ft_strncmp("PATH\0", path, 5))
	{
		while (temp)
		{
			if (temp->var
				&& ft_strncmp("_\0", temp->name, 2) != 0)
				ft_printf("%s=%s\n", 1, temp->name,
					temp->var);
			temp = temp->next;
		}
		ft_printf("_=/bin/env\n", 1);
		g_lobal.exit_code = 0;
	}
	else
		ft_error2("command not found", "env", 127);
	free_string(&path);
}
