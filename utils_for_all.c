/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:26:28 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/27 13:39:39 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_tab(char ***tab, int *count, char *param)
{
	char	**temp;
	int		l;

	*count = *count + 1;
	temp = *tab;
	*tab = (char **)ft_calloc((*count) + 1, sizeof(char *));
	if (!*tab)
		return (0);
	if (temp)
	{
		l = 0;
		while (temp[l])
		{
			(*tab)[l] = ft_strdup(temp[l]);
			free (temp[l]);
			l++;
		}
		free(temp);
		if (!((*tab)[l - 1]))
			return (0);
	}
	(*tab)[*count - 1] = ft_strdup(param);
	if (!((*tab)[*count - 1]))
		return (0);
	return (1);
}

int	add_to_int_tab(int **tab, int count, int param)
{
	int	*temp;
	int	l;

	temp = *tab;
	*tab = (int *)ft_calloc(count + 1, sizeof(int));
	if (!*tab)
		return (0);
	if (temp)
	{
		l = 0;
		while (temp[l])
		{
			(*tab)[l] = temp[l];
			l++;
		}
		free(temp);
		if (!((*tab)[l - 1]))
			return (0);
	}
	(*tab)[count - 1] = param;
	if (!((*tab)[count - 1]))
		return (0);
	return (1);
}

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

void	ft_free_data_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (data->cmd[i].tok)
			ft_del_stringtab(&(data->cmd[i].tok));
		i++;
	}
	free (data->cmd);
	data->cmd = NULL;
}

void	ft_free(t_data *data, char **token)
{
	if (token)
		ft_del_stringtab(&token);
	if (data)
	{
		if (data->cmd)
			ft_free_data_cmd(data);
		// if (data->envp)
		// 	free envp avec ft_del_strintab
		data = NULL;
	}

}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	ft_exit(int	i, char *str)
{
	printf("%s\n", str);
	exit (i);
}

