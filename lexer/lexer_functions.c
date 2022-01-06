#include "minishell.h"

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
	while (input[i])
	{
		if (input[i] == q)
			return (1);
		i++;
	}
	return (0);
}

void	function_0(t_lex *lex, char ***token)
{
	create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}

void	function_1(t_lex *lex, char ***token)
{
	if (ft_strchr("|<>", (lex->input)[lex->i]))
		add_to_token(token, lex, (lex->input)[lex->i++]);
	else if ((lex->input)[lex->i] != '\n')
	{
		create_new_token(token, lex);
		add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	function_2(t_lex *lex, char ***token)
{
	char	c;

	c = lex->input[lex->i];
	add_to_token(token, lex, (lex->input)[lex->i++]);
	if ((is_paired(c, lex->input, lex->i)))
	{
		while (lex->input[lex->i] != c)
			add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	function_3(t_lex *lex, char ***token)
{
	if (lex->token_nb > 0)
		create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}

void	function_4(t_lex *lex, char ***token)
{
	char ***temp;

	while ((lex->input)[lex->i] == ' ')
		lex->i++;
	temp = token;
}

void	function_5(t_lex *lex, char ***token)
{
	add_to_token(token, lex, (lex->input)[lex->i++]);
}

void	function_6(t_lex *lex, char ***token)
{
	if (lex->tok_char_nb != 0)
		create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}