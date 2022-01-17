/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:26:28 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/17 13:20:02 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab %d = %s\n", i, tab[i]);
		i++;
	}
	return ;
}

void	print_int_table(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("grammar %d = %d\n", i, tab[i]);
		i++;
	}
	return ;
}

void	ft_del_stringtab(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab)[i])
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
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
