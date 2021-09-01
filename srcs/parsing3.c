#include "../includes/minishell.h"

void debug(int d_apici, int s_apici, int prev_apici)
{
	printf("\n Debbug:\n");
	if (prev_apici == 1)
		printf("\t Primo apice singolo\n");
	if (prev_apici == 2)
		printf("\t Primo apice doppio\n");
	printf("\t Apice singolo: %d\n", s_apici);
	printf("\t Apice dpppio: %d\n", d_apici);
}

int first_apice(char *line)
{
	int i;

	i = 0;
	while (line[i++] != '\0')
	{
		if (line[i] == 39)
			return (1);
		else if (line[i] == 34)
			return (2);
	}
	return (0);
}

int check_cond(int prev_apice, int d_apici, int s_apici)
{
	debug(d_apici, s_apici, prev_apice);
	if (prev_apice == 1 && s_apici % 2 != 0 && d_apici % 2 == 0 && d_apici != 0)
		return (1);
	if (prev_apice == 2 && d_apici % 2 != 0 && s_apici % 2 == 0 && s_apici != 0)
		return (1);
	return (0);
}


int check_apertura(char *line)
{
	int i;
	int prev_apice;
	int s_apici;
	int d_apici;

	s_apici = 0;
	d_apici = 0;
	i = 0;
	prev_apice = first_apice(line);
	while (line[i] != '\0')
	{
		if (line[i] == 34)
		{
			d_apici += 1;
			if (check_cond(prev_apice, d_apici, s_apici) == 1)
				return (1);
		}
		if (line[i] == 39)
		{
			s_apici += 1;
			if (check_cond(prev_apice, d_apici, s_apici) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_corr_pos_apici(char *line)
{
	if (check_apertura(line) == 1)
	{
		if (first_apice(line) == 1)
			printf("Errore hai inserito in modo incorretto gli apici singoli\n");
		if (first_apice(line) == 2)
			printf("Errore hai inserito in modo incorretto gli apici doppi\n");
		return (0);
	}
	return (1);
}