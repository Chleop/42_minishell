/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:06:37 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/22 15:16:43 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	finish_cd(t_data *data, t_cd *cd)
{
	char	*temp;
	char	*pwd;

	if (cd->oldpwd)
	{
		temp = ft_strjoin("OLDPWD=", cd->oldpwd);
		add_to_envp(data->envp, temp);
		free_string(&temp);
	}
	pwd = get_var(data->envp, "PWD");
	if (pwd)
	{
		temp = ft_strjoin("PWD=", cd->path);
		add_to_envp(data->envp, temp);
		free_string(&temp);
		free_string(&pwd);
	}
}

int	chdir_path(t_data *data, t_cd *cd)
{
	if (cd->path)
	{
		if (chdir(cd->path) == -1)
		{
			ft_error2(strerror(errno), cd->path, 1);
			free_cd(&cd);
			return (0);
		}
		else
			finish_cd(data, cd);
	}
	else
	{
		free_cd(&cd);
		return (0);
	}
	free_cd(&cd);
	return (1);
}

void	set_path_envp(t_data *data, t_cd *cd, char *name)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strncmp(name, temp->name, ft_strlen(temp->name)) == 0
			&& temp->var)
		{
			cd->path = ft_strdup(temp->var);
			return ;
		}
		temp = temp->next;
	}
	ft_error2("cd: variable not set:", name, 1);
}

int	ft_cd(t_cmd *cmd)
{
	t_cd	*cd;

	cd = NULL;
	if (!init_cd(cmd, &cd))
		return (0);
	if (!cmd->param[1])
		set_path_envp(cmd->data, cd, "HOME");
	else if (cmd->param[1][0] == '-' && cmd->param[1][1] == '\0')
		set_path_envp(cmd->data, cd, "OLDPWD");
	else if (cmd->param[1][0] == '/')
		set_curpath(cd, cmd->param[1]);
	else
		set_path_dots(cmd, cd);
	return (chdir_path(cmd->data, cd));
}
