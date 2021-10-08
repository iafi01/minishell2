#include "../includes/minishell.h"

// int	ft_check_apici(char *line)
// {
// 	int	i;
// 	int	a;
// 	int	da;

// 	da = 0;
// 	a = 0;
// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (line[i] == '"')
// 			da++;
// 		if (line[i] == 39)
// 			a++;
// 	}
// 	if (da % 2 != 0)
// 		return (0);
// 	if (a % 2 != 0)
// 		return (0);
// 	return (1);
// }

int ft_apici_pari(char *line)
{	
	int i;
	int apici_d;
	int apici_s;

	apici_d = 0;
	apici_s = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
			apici_d++;
		if (line[i] == 39)
			apici_s++;
		i++;
	}
	if (apici_d % 2 == 0 && apici_s % 2 == 0)
		return (0);
	return (1);
}

int first_apice_index(char *line)
{
	int i;

	i = 0;
	while (line[i++] != '\0')
	{
		if (line[i] == 39)
			return (i);
		else if (line[i] == 34)
			return (i);
	}
	return (i);
}

int ft_apici_incrociati(char *line, int len)
{
	int i;
	int first;

	first = first_apice(line);
	int first_index = first_apice_index(line);
	i = 0;
	while (line[len])
	{
		if (line[len] == first)
			return (ft_apici_incrociati(line+first_index, len));
		else if ((line[len] == 39 && first == 34) || (line[len] == 34 && first == 39))
			return (1);
		len--;
	}
}

int init_parsing(char *line)
{
	if (solo_spazi(line))
		return (-1);
	if (ft_apici_pari(line))
		return (1);
	if (ft_apici_incrociati(line, ft_strlen(line)))
		return (1);
	return (0);
}
