/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:23:36 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/10 18:54:40 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_stringtab(char ***tab)
{
	int	i;

	i = 0;
	if (!*tab)
		return ;
	while ((*tab)[i])
	{
		if ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	ft_free_parser(t_data *data, char ***token)
{
	int	i;

	i = 0;
	if (*token)
		ft_del_stringtab(token);
	if (data->cmd)
	{
		while (i < data->nr_cmds)
		{
			if (data->cmd[i].tok)
				ft_del_stringtab(&(data->cmd[i].tok));
			if (data->cmd[i].qualif)
				free(data->cmd[i].qualif);
			i++;
		}
	}
	if (data->pipe_index)
		free(data->pipe_index);
}

void	delete_here_file(t_data *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		ft_error2("Error: malloc failed", NULL, data, 1);
		return ;
	}
	cmd->param = ft_calloc(4, sizeof(char *));
	cmd->param[0] = ft_strdup("/bin/rm");
	cmd->param[1] = ft_strdup("-rf");
	cmd->param[2] = ft_strdup(data->here_doc);
	cmd->param[3] = NULL;
	cmd->id = 0;
	cmd->data = data;
	cmd->nr_param = 1;
	cmd->nr_in = 0;
	cmd->nr_out = 0;
	data->process_id[0] = 0;
	fork_function(cmd);
	waitpid(data->process_id[0], NULL, 0);

	// char	**rm;
	// char	**envp_tab;

	// rm = ft_calloc(4, sizeof(char *));
	// rm[0] = ft_strdup("/bin/rm");
	// rm[1] = ft_strdup("-rf");
	// rm[2] = data->here_doc;
	// rm[3] = NULL;
	// convert_envp(data->envp, &envp_tab);
	// if (execve(rm[0], rm, envp_tab) == -1)
	// 	ft_error2(strerror(errno), "rm", data, 126);
	// ft_del_stringtab(&envp_tab);
	// ft_del_stringtab(&rm);
}


void	ft_free_data(t_data *data, int code)
{
	int	i;

	i = 0;
	if (code)
		free_envp(data);
	if (data->here_doc)
		delete_here_file(data);
	if (data->cmd)
	{
		while (i < data->nr_cmds)
		{
			if (data->cmd[i].param)
				ft_del_stringtab(&(data->cmd[i].param));
			if (data->cmd[i].i)
				ft_del_stringtab(&(data->cmd[i].i));
			if (data->cmd[i].o)
				ft_del_stringtab(&(data->cmd[i].o));
			if (data->cmd[i].type)
				free((data->cmd[i].type));
			i++;
		}
		free (data->cmd);
		data->cmd = NULL;
	}
}
