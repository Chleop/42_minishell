/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:17:40 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 15:42:28 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_cd(t_data *data, char *pwd, char *oldpwd)
{
	//if (!ft_stncmp(data->envp))
	
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

char	*chdir_var(t_data *data, char *name)
{
	int		i;
	t_envp	*temp;
	char	*path;

	i = -1;
	temp = data->envp;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(temp->name)) && temp->var)
		{
			path = ft_strdup(temp->var);
			if (chdir(path) == -1)
				perror("error - cd");
			else
				return (path);
		}
		temp = temp->next;
	}
	ft_printf("%s%s%s\n", "cd: ", name, " not set");
	return (NULL);
}

char	*get_var(t_envp *envp, char *name)
{
	t_envp	*temp;

	temp = envp;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(temp->name)))
			return (ft_strdup(temp->var));
		temp = temp->next;
	}
	return (NULL);
}

void	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	oldpwd = NULL;
	oldpwd = get_var(cmd->data->envp, "PWD");
	if (cmd->param[1] == NULL)
		pwd = chdir_var(cmd->data, "HOME");
	else if (cmd->param[1][0] == '-' && cmd->param[1][1] == '\0')
		pwd = chdir_var(cmd->data, "OLDPWD");
	else if (cmd->param[1][0] == '/')
	{
		if (chdir(cmd->param[1]) == -1)
			perror("error - cd");
		else
			pwd = ft_strdup(cmd->param[1]);
	}
	else
		pwd = handle_dots(cmd, oldpwd);
	if (pwd)
		finish_cd(cmd->data, pwd, oldpwd);
}
