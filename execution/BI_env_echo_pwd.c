/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/10 13:12:45 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", 1, pwd);
	free_string(&pwd);
}

int	no_backslash(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->param[1][i] == 'n')
		i++;
	if (cmd->param[1][i] != '\0')
		return (0);
	else
		return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd->param[1] == NULL)
	{
		ft_printf("\n", 1);
		return ;
	}
	else if (ft_strncmp(cmd->param[1], "-n", 2) == 0)
		j = no_backslash(cmd);
	i = j;
	while (cmd->param[++i] && cmd->param[i + 1])
		ft_printf("%s ", 1, cmd->param[i]);
	if (j && cmd->param[i])
		ft_printf("%s", 1, cmd->param[i]);
	else if (j)
		printf("");
	else
		ft_printf("%s\n", 1, cmd->param[i]);
}

void	ft_env(t_cmd *cmd)
{
	char	*path;
	t_envp	*temp;

	temp = cmd->data->envp;
	path = get_expansion(cmd->data, "PATH");
	if (cmd->param[1] != NULL)
		ft_error2("env: too many arguments", NULL, cmd->data, 1);
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
	}
	else
		ft_error2("command not found", "env", cmd->data, 1);
	free_string(&path);
}
