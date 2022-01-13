/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:55:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/13 20:02:43 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_token(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

void	initialize_grammar(int **grammar, int nb_token)
{
	int	i;

	i = 0;
	while (i < nb_token)
	{
		(*grammar)[i] = EMPTY;
		i++;
	}
	return ;
}

void	parse(char **token)
{
	int	*grammar;
	int	i;

// COMMENCER PAR SEPARER LES CMDS PAR PIPE
	grammar = (int *)ft_calloc(count_token(token) + 1, sizeof(int));
	if (!grammar)
		perror("Error ");
	initialize_grammar(&grammar, count_token(token));
	i = 0;
	while (token[i])
	{
		if (ft_strchr(token[i], '$'))
			grammar[i] = VAR;
		else if ((i > 0) && (ft_strchr(token[i - 1], '<')))
			grammar[i] = RED_I;
		else if ((i > 0) && (ft_strchr(token[i - 1], '>')))
			grammar[i] = RED_OS;
		else if ((i > 0) && (ft_strchr(token[i - 1], '>>')))
			grammar[i] = RED_OD;
		else if ((i > 0) && (ft_strchr(token[i - 1], '<<')))
			grammar[i] = HERE_END;
		else if ((i > 0) && (ft_strchr(token[i - 1], '>')))
			grammar[i] = RED_O;
// A REVOIR CAR LES OPERATEURS NE SONT PAS ENCORE NETTOYES !!!
		i++;
	}
	
	
	print_int_table(grammar);
	exit(1);
}