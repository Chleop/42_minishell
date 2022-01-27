#include "minishell.h"

void	print_char_table(char *str, char **tab)
{
	int	i;

	if (!tab)
	{
		printf("tab n'existe pas\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		printf("%s[%d] = [%s]\n",str, i, tab[i]);
		i++;
	}
	return ;
}

void	print_int_table(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("Int tab %d = %d\n", i, tab[i]);
		i++;
	}
	return ;
}

void	print_cmds_and_tokens(t_data *data)
{
	int i = 0;
	while (i < data->nr_cmds)
	{
		printf("Commande %d\n", i);
		print_char_table("Token", data->cmd[i].tok);
		print_int_table(data->cmd[i].qualif);
		i++;
	}
}

void	print_cmd_parameters(t_data *data)
{
	printf("LES PARAMETRES SONT:\n");
	int i = 0;
	while (i < data->nr_cmds)
	{
		printf ("Commande %d\n", i);
		print_char_table("Param", data->cmd[i].param);
		printf("Nb param = %d\nIn file = [%s]\nOut file = [%s] of type %d\n", 
		data->cmd[i].nr_param, data->cmd[i].i_file, data->cmd[i].o_file, 
		data->cmd[i].red_out_type);
		i++;
	}
}
