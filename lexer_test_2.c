#include "minishell.h"

void	print_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("Token %d = %s\n", i, tab[i]);
		i++;
	}
	return ;
}

void	ft_del_stringtab(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab)[i])
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
}

void	create_new_token(int *tok_char_nb, int *token_nb, char ***token, char input)
{
	int		l;
	char	**tab_temp;

	*tok_char_nb = 1;
	*token_nb = (*token_nb) + 1;
	if ((*token) == NULL)
		*token = ft_calloc(2, sizeof(char *));
	else
	{
		tab_temp = (*token);
		(*token) = ft_calloc(((*token_nb) + 1), sizeof(char *));
		l = 0;
		while (tab_temp[l])
		{
			(*token)[l] = tab_temp[l];
			l++;
		}
		free(tab_temp);
	}
	(*token)[(*token_nb) - 1] = ft_calloc((2), sizeof(char));
	(*token)[(*token_nb) - 1][0] = input;
	(*token)[(*token_nb) - 1][1] = '\0';
	(*token)[(*token_nb)] = NULL;
}

void	add_to_token(int *tok_char_nb, int token_nb, char ***token, char input)
{
	int		l;
	char	*str_temp;

	*tok_char_nb = *tok_char_nb + 1;
	str_temp = (*token)[token_nb - 1];
	(*token)[token_nb - 1] = ft_calloc(((*tok_char_nb) + 1), sizeof(char));
	l = 0;
	while (str_temp[l])
	{
		(*token)[token_nb - 1][l] = str_temp[l];
		l++;
	}
	free(str_temp);
	(*token)[token_nb - 1][(*tok_char_nb) - 1] = input;
	(*token)[token_nb - 1][(*tok_char_nb)] = '\0';
}

int	is_new_token(char **token, char input, int *i)
{
	int	new_token;

	new_token = 0;
	if (token == NULL)
		new_token = 1;
	else if (input == ' ')
	{
		*i = *i + 1;
		new_token = 1;
	}
	return(new_token);
}

char	**split_into_token(char *input)
{
	int		i;
	int		token_nb;
	int		tok_char_nb;
	char	**token;

	i = 0;
	token_nb = 0;
	tok_char_nb = 0;
	token = NULL;
	while (input[i])
	{
		if (input[i] == '\n')
			break;
		else if (is_new_token(token, input[i], &i))
			create_new_token(&tok_char_nb, &token_nb, &token, input[i]);
		else
			add_to_token(&tok_char_nb, token_nb, &token, input[i]);
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
