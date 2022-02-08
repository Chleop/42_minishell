/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:35:11 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/08 16:21:29 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_curpath(char *string)
{
	int		i;
	int		j;
	char	*curpath;

	i = 0;
	j = 0;
	curpath = NULL;
	while (string[i] != '\0')
	{
		if (string[i] != '/' || (string[i] == '/'
			&& !(string[i + 1] == '/' || string[i + 1] == '\0')))
			j++;
		i++;
	}
	if (j)
		curpath = ft_calloc(j + 1, sizeof(char));
	return (curpath);
}

char	*set_curpath(char *string)
{
	int		i;
	int		j;
	char	*curpath;

	i = 0;
	j = 0;
	curpath = malloc_curpath(string);
	while (string[i])
	{
		if (string[i] != '/' || (string[i] == '/'
			&& !(string[i + 1] == '/' || string[i + 1] == '\0')))
		{
			curpath[j] = string[i];
		 	j++;
		}
		i++;
	}
	if (!j)
		curpath = ft_strdup("/");
	return (curpath);
}
