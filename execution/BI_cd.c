/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:06:37 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/08 17:29:15 by avan-bre         ###   ########.fr       */
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
		free_string(temp);
	}
	pwd = get_var(data->envp, "PWD");
	if (pwd)
	{
		temp = ft_strjoin("PWD=", cd->path);
		add_to_envp(data->envp, temp);
		free_string(temp);
		free_string(pwd);
	}
}

void	chdir_path(t_data *data, t_cd *cd)
{
	if (chdir(cd->path) == -1)
	{
		perror("error - cd");
		//exit code should be 128
	}
	else
		finish_cd(data, cd);
	free_string(cd->oldpwd);
	free_string(cd->path);
	free_string(cd->current);
	free(cd);
	cd = NULL;
}

void	chdir_envp(t_data *data, t_cd *cd, char *name)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strncmp(name, temp->name, ft_strlen(temp->name)) == 0
			&& temp->var)
		{
			cd->path = ft_strdup(temp->var);
			chdir_path(data, cd);
			return ;
		}
		temp = temp->next;
	}
	ft_printf("%s%s%s\n", 2, "cd: ", name, " not set");
	free_string(cd->oldpwd);
	free(cd);
	cd = NULL;
}

void	ft_cd(t_cmd *cmd)
{
	t_cd	*cd;

	cd = NULL;
	if (!init_cd(cmd, &cd))
		return ;
	if (!cmd->param[1])
		chdir_envp(cmd->data, cd, "HOME");
	else if (cmd->param[1][0] == '-' && cmd->param[1][1] == '\0')
		chdir_envp(cmd->data, cd, "OLDPWD");
	else if (cmd->param[1][0] == '/')
	{
		cd->path = set_curpath(cmd->param[1]);
		chdir_path(cmd->data, cd);
	}
	else
		handle_dots(cmd, cd);
}
