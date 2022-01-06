#include "minishell.h"

void	init_lexer(t_lex *lex, char *input)
{
	lex->input = input;
	lex->i = 0;
	lex->token_nb = 0;
	lex->tok_char_nb = 0;
}

int	condition_tree(t_lex *lex, char ***token)
{
	if (!(*token))
		return (0);
	else if (ft_strchr("|<>", (lex->input)[lex->i - 1]))
		return (1);
	else if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
		return (2);
	else if (ft_strchr("|<>", (lex->input)[lex->i]))
		return (3);
	else if ((lex->input)[lex->i] == ' ')
		return (4);
	else if (!(ft_strchr("|<> ", (lex->input)[lex->i - 1])))
		return (5);
	else
		return (6);
}

char	**split_into_token(char *input)
{
	t_lex		*lex;
	char		**token;
	int			met_condition;
	static void	(*function_table[8])(t_lex *lex, char ***token) = {
		function_0,
		function_1,
		function_2,
		function_3,
		function_4,
		function_5,
		function_6,
		NULL,
	};

	lex = ft_calloc(1, sizeof(t_lex));
	init_lexer(lex, input);
	token = NULL;
	while ((lex->input)[lex->i] != '\n')
	{
		met_condition = condition_tree(lex, &token);
		function_table[met_condition](lex, &token);
	}
	return (token);
}
