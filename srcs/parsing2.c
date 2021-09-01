#include "../includes/minishell.h"

int	solo_spazi(char *line)
{
	int i;
	size_t space;

	i = 0;
	space = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == '\v'   
			|| line[i] == '\f' || line[i] == '\r' || line[i] == 32)
		    space++;
        i++;
	}
	if (ft_strlen(line) == space)
        return (0);
	return (1);
}

// int check_cond(int prev_apice, int d_apici, int s_apici)
// {
// 	if (s_apici % 2 != 0 && d_apici % 2 != 0)
// 		return (0);
// 	if (prev_apice == 1 && s_apici % 2 != 0 && d_apici % 2 == 0)
// 		return (0);
// 	if (prev_apice == 2 && d_apici % 2 != 0 && s_apici % 2 == 0)
// 		return (0);
// 	if (prev_apice == 1 && s_apici % 2 == 0 && d_apici % 2 != 0)
// 		return (1);
// 	if (prev_apice == 2 && d_apici % 2 == 0 && s_apici % 2 != 0)
// 		return (1);
// 	return (2);
// }

// int first_apice(char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i++] != '\0')
// 	{
// 		if (line[i] == 39)
// 			return (1);
// 		else if (line[i] == 34)
// 			return (2);
// 	}
// 	return (0);
// }

// int check_apertura(char *line, int s_apici, int d_apici)
// {
// 	int i;
// 	int prev_apice;

// 	i = 0;
// 	prev_apice = first_apice(line);
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == 34)
// 		{
// 			s_apici += 1;
// 		}
// 		if (line[i] == 39)
// 		{
// 			d_apici += 1;
// 		}
// 		i++;
// 	}
// 	if (check_cond(prev_apice, d_apici, s_apici) == 1)
// 		return (1);
// 	if (check_cond(prev_apice, d_apici, s_apici) == 1)
// 		return (1);
// 	return (0);
// }

// int	check_corr_pos_apici(char *line)
// {
// 	if (check_apertura(line, 0, 0) == 1)
// 	{
// 		if (first_apice(line) == 1)
// 			printf("Errore hai inserito in modo incorretto gli apici singoli\n");
// 		if (first_apice(line) == 2)
// 			printf("Errore hai inserito in modo incorretto gli apici doppi\n");
// 		return (0);
// 	}
// 	return (1);
// }
