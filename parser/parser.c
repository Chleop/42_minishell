/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:55:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/18 18:19:30 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_data *data, char **token)
{
	int	*grammar;
	// int	i;

	if (!initialize_data(data, token))
		return (0);
	if (!initialize_cmds(data, token))
		return (0);
	print_cmds_and_tokens(data);
	grammar = (int *)ft_calloc(data->nr_token + 1, sizeof(int));
	if (!grammar)
		return (ft_error("Error:malloc failed\n"));
	initialize_grammar(&grammar, data->nr_token);
	// exit(1);
// 	i = 0;
// 	while (token[i])
// 	{
// 		if (ft_strchr(token[i], '$'))
// 			grammar[i] = VAR;
// 		else if ((i > 0) && (ft_strchr(token[i - 1], '<')))
// 			grammar[i] = RED_IN;
// 		else if ((i > 0) && (ft_strchr(token[i - 1], '>')))
// 			grammar[i] = RED_OUT_S;
// 		// else if ((i > 0) && (ft_strchr(token[i - 1], '>>')))
// 		// 	grammar[i] = RED_OUT_D;
// 		// else if ((i > 0) && (ft_strchr(token[i - 1], '<<')))
// 		// 	grammar[i] = HERE_END;

// // A REVOIR CAR LES OPERATEURS NE SONT PAS ENCORE NETTOYES !!!
// 		i++;
// 	}
	
	
	print_int_table(grammar);
	if (grammar)
	{
		free (grammar);
		grammar = NULL;
	}
	return (1);
}