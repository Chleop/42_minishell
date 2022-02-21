/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:38:24 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 15:00:59 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_SOURCE
# define PURPLE "\001\e[0;35m\002"
# define GREEN "\001\e[0;32m\002"
# define RESET "\001\e[0m\002"

# include "libft.h"
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"
# include "execute.h"

# ifndef GLOBAL_SIG
#  define GLOBAL_SIG

extern int	e_code;
extern int	g_sig;
# endif

int		ft_error2(char *string, char *name, t_data *data, int code);
void	signal_handler(void);

#endif