/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/07 13:55:54 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", 1, pwd);
	free_string(pwd);
	exit(0);
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
	if (j)
		ft_printf("%s", 1, cmd->param[i]);
	else
		ft_printf("%s\n", 1, cmd->param[i]);
	ft_free_data(cmd->data, 1);
	exit(0);
}

// void	ft_echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	// printf ("exit code= %d\n", exit_code);
// 	if (cmd->param[1] == NULL)
// 	{
// 		ft_printf("\n", 1);
// 		return ;
// 	}
// 	else if (ft_strncmp(cmd->param[1], "-n", 2) == 0)
// 		j = no_backslash(cmd);
// 	i = j;
// 	while (cmd->param[++i] && cmd->param[i + 1])
// 	{
// 		if (ft_strncmp(cmd->param[i], "$?\0", 3) == 0)
// 		{
// 			ft_printf("%d ", 1, exit_code);
// 			exit_code = 0;
// 		}
// 		else
// 			ft_printf("%s ", 1, cmd->param[i]);
// 	}
// 	if (j)
// 	{
// 		if (ft_strncmp(cmd->param[i], "$?\0", 3) == 0)
// 		{
// 			ft_printf("%d", 1, exit_code);
// 			exit_code = 0;
// 		}
// 		else
// 			ft_printf("%s", 1, cmd->param[i]);
// 	}	
// 	else
// 	{
// 		if (ft_strncmp(cmd->param[i], "$?\0", 3) == 0)
// 		{
// 			ft_printf("%d\n", 1, exit_code);
// 			exit_code = 0;
// 		}
// 		else
// 			ft_printf("%s\n", 1, cmd->param[i]);
// 	}
// 	ft_free_data(cmd->data, 1);
// 	exit(0);
// }

void	ft_env(t_cmd *cmd)
{
	char	*path;

	path = get_expansion(cmd->data, "PATH");
	if (cmd->param[1] != NULL)
		ft_printf("env: too many arguments\n", 2);
	else if (ft_strncmp("PATH\0", path, 5))
	{
		while (cmd->data->envp)
		{
			if (cmd->data->envp->var
				&& ft_strncmp("_\0", cmd->data->envp->name, 2) != 0)
				ft_printf("%s=%s\n", 1, cmd->data->envp->name,
					cmd->data->envp->var);
			cmd->data->envp = cmd->data->envp->next;
		}
		ft_printf("_=/bin/env\n", 1);
	}
	else
		ft_printf("%s\n", 2, "command not found: env");
	ft_free_data(cmd->data, 1);
	free_string(path);
	exit (0);
}
