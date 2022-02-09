/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:57:26 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/09 12:22:17 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	numeric_string(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '-' || string[i] == '+')
		i++;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

int	final_status(unsigned long long code, int neg)
{
	int	ret;

	ret = 0;
	if (code < 256 && code >= 0 && neg > 0)
		ret = code;
	else
		ret = (code * neg) % 256;
	return (ret);
}

int	calculate_status(char *string)
{
	unsigned long long	code;
	int					neg;
	int					i;

	neg = 1;
	code = 0;
	i = 0;
	while (ft_isspace(string[i]))
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(string[i]))
	{
		code = code * 10 + (string[i] - '0');
		if ((neg == 1 && code > 9223372036854775807ULL)
			|| (neg == -1 && code > 9223372036854775808ULL))
			return (-1);
		i++;
	}
	return (final_status(code, neg));
}

void	ft_exit(t_cmd *cmd)
{
	int	code;

	ft_printf("%s\n", 1, "exit");
	code = 0;
	if (cmd->param[1] == NULL)
		code = 0;
	//code = exit_code?
	else if (cmd->param[2] != NULL)
	{
		ft_printf("%s\n", 2, "exit: too many argurments");
		return ;
	}
	else if (!numeric_string(cmd->param[1]))
	{
		ft_printf("%s\n", 2, "exit: numeric argument required");
		code = 2;
	}
	else
		code = calculate_status(cmd->param[1]);
	if (code == -1)
	{
		ft_printf("%s\n", 2, "exit: numeric argument required");
		code = 2;
	}
	ft_free_data(cmd->data, 1);
	exit (code);
}
