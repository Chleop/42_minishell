/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:26:28 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/07 14:26:31 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("Token %d = %s\n", i, tab[i]);
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
