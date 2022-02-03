/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:26:28 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/03 18:23:25 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_tab(char ***tab, int *count, char *param)
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

int	add_int(int **tab, int count, int param)
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

int	ft_error(char *str)
{
	ft_printf("%s\n", 2, str);
	return (0);
}

// int	ft_error2(char *str, int code)
// {
// 	ft_printf("%s\n", 2, str);
// 	exit_code = code;
// 	return (0);
// }

void	final_exit(t_data *data, char *str)
{
	ft_printf("%s\n", 2, str);
	free_envp(data);
	exit (1);
	// exit (exit_code);
}
