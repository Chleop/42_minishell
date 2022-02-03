/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:38:24 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 18:17:09 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

struct	s_envp;
struct	s_data;

extern int			exit_code;

typedef struct s_cmd
{
	int				nr_tok;
	char			**tok;
	int				*qualif;
	int				nr_param;
	char			**param;
	int				nr_in;
	char			**i;
	int				*fd_i;
	int				nr_out;
	char			**o;
	int				*fd_o;
	int				*type;
	int				id;
	struct s_data	*data;
}	t_cmd;

typedef struct s_pars
{
	int	pipe[1023];
}	t_pars;

typedef struct	s_data
{
	struct s_envp	*envp;
	int				nr_token;
	int				nr_cmds;
	t_cmd			*cmd;
	t_pars			parser;
	int				pipe[2];
	int				pipe_fd[1023][2];
	int				process_id[1024];
}	t_data;

# include "parser.h"
# include "execute.h"

#endif