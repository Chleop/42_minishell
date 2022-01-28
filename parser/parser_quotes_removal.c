/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_removal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/28 18:06:47 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_before_quotes(char **token, char *temp, int firstq_i)
{
	int		start;
	int		end;

	start = 0;
	end = firstq_i;
	ft_memcpy(*token + start, temp + start, end - start);
	return ;
}

void	cpy_between_quotes(char **token, char *temp, int firstq_i, int secondq_i)
{
	int		start;
	int		end;

	start = firstq_i;
	end = secondq_i;
	ft_memcpy(*token + start, temp + start + 1, end - start - 1);
	return ;
}

void	cpy_after_quotes(char **token, char *temp, int secondq_i)
{
	int		start;
	int		end;

	start = secondq_i;
	end = ft_strlen(temp);
	ft_memcpy(*token + start - 1, temp + start + 1, end - start - 1);
	return ;
}

int	remove_quotes(char **token, int firstq_i, int secondq_i)
{
	char	*temp;

	temp = *token;
	*token = ft_calloc(ft_strlen(temp) - 1, sizeof(char));
	if (!*token)
		return (ft_error("Error: malloc failed"));
	cpy_before_quotes(token, temp, firstq_i);
	cpy_between_quotes(token, temp, firstq_i, secondq_i);
	if (temp[secondq_i + 1])
		cpy_after_quotes(token, temp, secondq_i);
	free (temp);
	temp = NULL;
	return (1);
}

int	identify_remove_quotes(char **token)
{
	int	firstq_i;
	int	secondq_i;
	int	quote;

	quote = is_quoted(*token);
	if (quote)
	{
		firstq_i = ft_strchr(*token, quote) - *token;
		secondq_i = ft_strchr(*token + firstq_i + 1, quote) - *token;
		if (!remove_quotes(token, firstq_i, secondq_i))
			return (0);
	}
	return (1);
}
