/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:17:40 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/02 12:18:55 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_cd(t_data *data, char *pwd, char *oldpwd)
{
	size_t	i;
	char	*temp;

	i = ft_strlen(pwd);
	if (ft_strlen(oldpwd) > i)
		i = ft_strlen(oldpwd);
	if (ft_strncmp(pwd, oldpwd, i) != 0)
	{
		temp = oldpwd;
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		add_to_envp(data->envp, oldpwd);
		free_string(temp);
		temp = pwd;
		pwd = ft_strjoin("PWD=", pwd);
		add_to_envp(data->envp, pwd);
		free_string(temp);
	}
	free_string(oldpwd);
	free_string(pwd);
}

void	chdir_var(t_data *data, char *var)
{
	int		i;
	t_envp	*temp;

	i = -1;
	temp = data->envp;
	while (temp)
	{
		if (ft_strncmp(var, temp->name, 5) == 0 && temp->var != NULL)
		{
			if (chdir(temp->var) == -1)
				perror("error - cd");
			return ;
		}
		temp = temp->next;
	}
	ft_printf("%s%s%s\n", "cd: ", var, " not set");
}

void	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (cmd->param[1] == NULL)
		chdir_var(cmd->data, "HOME");
	else if (cmd->param[1][0] == '-' && cmd->param[1][1] == '\0')
		chdir_var(cmd->data, "OLDPWD");
	else if (cmd->param[1][0] == '/')
	{
		if (chdir(cmd->param[1]) == -1)
			perror("error - cd");
	}
	else
		handle_dots(cmd);
	pwd = getcwd(NULL, 0);
	finish_cd(cmd->data, pwd, oldpwd);
}
