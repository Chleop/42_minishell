#include "minishell.h"

void	init_lexer(t_lex *lex, char *input)
{
	lex->input = input;
	lex->i = 0;
	lex->token_nb = 0;
	lex->tok_char_nb = 0;
	lex->inside_quotes = '\0';
}

void	create_new_token(char ***token, t_lex *lex)
{
	int		l;
	char	**tab_temp;

	while ((lex->input)[lex->i] == ' ')
		lex->i++;
	if ((lex->input)[lex->i] == '\n')
		return ;
	lex->tok_char_nb = 0;
	lex->token_nb = (lex->token_nb) + 1;
	// printf("Creating token %d for input %c\n", lex->token_nb, (lex->input)[lex->i]);
	tab_temp = (*token);
	*token = ft_calloc((lex->token_nb + 1), sizeof(char *));
	if (tab_temp)
	{
		l = 0;
		while (tab_temp[l])
		{
			(*token)[l] = tab_temp[l];
			l++;
		}
		free(tab_temp);
	}
}

void	add_to_token(char ***token, t_lex *lex, char input)
{
	int		l;
	char	*str_temp;

	// printf("Adding %c to token %d\n", input, lex->token_nb);
	if (input != '\n')
	{
		lex->tok_char_nb = lex->tok_char_nb + 1;	
		str_temp = (*token)[lex->token_nb - 1];
		(*token)[lex->token_nb - 1] = ft_calloc((lex->tok_char_nb + 1), sizeof(char));
		if (str_temp)
		{
			l = 0;
			while (str_temp[l])
			{
				(*token)[lex->token_nb - 1][l] = str_temp[l];
				l++;
			}
			free(str_temp);
		}
		(*token)[lex->token_nb - 1][lex->tok_char_nb - 1] = input;
	}
}

int	is_paired(char q, char *input, int i)
{
	i++;
	while (input[i])
	{
		if (input[i] == q)
			return (1);
		i++;
	}
	return (0);
}

char	**split_into_token(char *input)
{
	t_lex	*lex;
	char	**token;

	lex = ft_calloc(1, sizeof(t_lex));
	init_lexer(lex, input);
	token = NULL;
	while ((lex->input)[lex->i] != '\n')
	{
		if (!token)
			create_new_token(&token, lex);
		if ((ft_strchr("|<> ", (lex->input)[lex->i])) && (!lex->inside_quotes))
		{
			if (lex->i)
				create_new_token(&token, lex);
			if (ft_strchr("|<>", (lex->input)[lex->i]))
			{
				while (ft_strchr("|<>", (lex->input)[lex->i]))
					add_to_token(&token, lex, (lex->input)[lex->i++]);
				create_new_token(&token, lex);
			}
		}
		else if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
		{
			if (!(lex->inside_quotes) && (is_paired((lex->input)[lex->i], lex->input, lex->i)))
				lex->inside_quotes = lex->input[lex->i];
			else if (lex->inside_quotes == lex->input[lex->i])
				lex->inside_quotes = '\0';
			add_to_token(&token, lex, (lex->input)[lex->i++]);
		}
		// else if ((lex->input)[lex->i] == '$')
		// {
		// 	if (lex->token_nb > 1)
		// 		create_new_token(&token, lex);
		// 	add_to_token(&token, lex, (lex->input)[lex->i++]);
		// }
		else
			add_to_token(&token, lex, (lex->input)[lex->i++]);
	}
	return(token);
}

int	main(int argc, char **argv)
{
	char	*input;
	char	**token;

	if (argc > 1)
		printf("Error: too many arguments");
	if (ft_strncmp(argv[0], "./minishell", 11))
		printf("Error: ");
	while (42)
	{
		ft_putstr_fd("minishou:~$ ", 1);
		input = get_next_line(0);

		token = split_into_token(input);
		free (input);
		print_table(token);
		ft_del_stringtab(&token);
	}
	return (0);
}
	