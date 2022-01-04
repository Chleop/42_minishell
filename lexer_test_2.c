#include "minishell.h"

void	init_lexer(char ***token, t_lex *lex, char *input)
{
	lex->input = input;
	*token = ft_calloc(2, sizeof(char *));;
	lex->token_nb = 1;
	(*token)[(lex->token_nb) - 1] = ft_calloc(1, sizeof(char));
	(*token)[(lex->token_nb)] = NULL;
	lex->tok_char_nb = 0;
	lex->inside_quotes = '\0';
}

void	create_new_token(char ***token, t_lex *lex)
{
	int		l;
	char	**tab_temp;

	lex->tok_char_nb = 0;
	lex->token_nb = (lex->token_nb) + 1;
	tab_temp = (*token);
	(*token) = ft_calloc(((lex->token_nb) + 1), sizeof(char *));
	l = 0;
	while (tab_temp[l])
	{
		(*token)[l] = tab_temp[l];
		l++;
	}
	free(tab_temp);
	(*token)[(lex->token_nb) - 1] = ft_calloc(1, sizeof(char));
	(*token)[(lex->token_nb)] = NULL;
}

void	add_to_token(char ***token, t_lex *lex, char input)
{
	int		l;
	char	*str_temp;

	if (input != '\n')
	{
		lex->tok_char_nb = lex->tok_char_nb + 1;
		str_temp = (*token)[lex->token_nb - 1];
		(*token)[lex->token_nb - 1] = ft_calloc(((lex->tok_char_nb) + 1), sizeof(char));
		l = 0;
		while (str_temp[l])
		{
			(*token)[lex->token_nb - 1][l] = str_temp[l];
			l++;
		}
		free(str_temp);
		(*token)[lex->token_nb - 1][(lex->tok_char_nb) - 1] = input;
		(*token)[lex->token_nb - 1][(lex->tok_char_nb)] = '\0';
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
	int		i;

	lex = ft_calloc(1, sizeof(t_lex));
	init_lexer(&token, lex, input);
	i = 0;
	while (((lex->input)[i]) && ((lex->input)[i] != '\n'))
	{
		if ((!lex->inside_quotes) && (((lex->input)[i] == '|') || ((lex->input)[i] == ' ')))
		{
			while ((lex->input)[i + 1] == ' ')
				i++;
			create_new_token(&token, lex);
		}
		else
		{
			if (((lex->input)[i] == '\'') || ((lex->input)[i] == '\"'))
			{
				if (!(lex->inside_quotes) && (is_paired((lex->input)[i], lex->input, i)))
				{
					lex->inside_quotes = lex->input[i];
					i++;
				}
				else if (lex->inside_quotes == lex->input[i])
				{
					lex->inside_quotes = 0;
					i++;
				}
			}
			add_to_token(&token, lex, (lex->input)[i]);
		}
		i++;
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
