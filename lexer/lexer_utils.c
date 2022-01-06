/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:38:33 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/03 18:39:03 by cproesch         ###   ########.fr       */
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