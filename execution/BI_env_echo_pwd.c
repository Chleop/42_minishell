/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 16:17:44 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	ft_printf("%s\n", 1, getcwd(NULL, 0));
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
// 			ft_printf("%d ", 1, cmd->data->exit_code);
// 			cmd->data->exit_code = 0;
// 		}
// 		else
// 			ft_printf("%s ", 1, cmd->param[i]);
// 	}
// 	if (j)
// 	{
// 		if (ft_strncmp(cmd->param[i], "$?\0", 3) == 0)
// 		{
// 			ft_printf("%d", 1, cmd->data->exit_code);
// 			cmd->data->exit_code = 0;
// 		}
// 		else
// 			ft_printf("%s", 1, cmd->param[i]);
// 	}	
// 	else
// 	{
// 		if (ft_strncmp(cmd->param[i], "$?\0", 3) == 0)
// 		{
// 			ft_printf("%d\n", 1, cmd->data->exit_code);
// 			cmd->data->exit_code = 0;
// 		}
// 		else
// 			ft_printf("%s\n", 1, cmd->param[i]);
// 	}
// 	ft_free_data(cmd->data, 1);
// 	exit(0);
// }

void	ft_env(t_cmd *cmd)
{
	if (cmd->param[1] != NULL)
		ft_printf("env: too many arguments\n", 2);
	else
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
	ft_free_data(cmd->data, 1);
	exit (0);
}
