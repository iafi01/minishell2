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

char	ft_invert_apici(char c)
{
	if (c == 34)
		c = 39;
	if (c == 39)
		c = 34;
	return (c);
}

int	ft_store_apici(int *ap, char *line)
{
	int	i;

	ap[0] = 0;
	ap[1] = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34 && ap[0] != 0 && ap[1] == 0)
		{
			ap[1] = 2;
			i++;
			break ;
		}
		else if (line[i] == 39 && ap[0] != 0 && ap[1] == 0)
		{
			ap[1] = 1;
			i++;
			break ;
		}
		if (line[i] == 34 && ap[0] == 0)
			ap[0] = 2;
		else if (line[i] == 39 && ap[0] == 0)
			ap[0] = 1;
	}
	return (i);
}

int ft_apici_1(char *line)
{
	int i;
	int	ap[2];
	
	i = ft_store_apici(ap, line);
	if (ap[0] == 1 && ap[1] == 2)
		return (ft_apici_0(line + i));
	return (1);
}

int ft_apici_2(char *line)
{
	int i;
	int	ap[2];
	
	i = ft_store_apici(ap, line);
	if (ap[0] == 2 && ap[1] == 1)
		return (ft_apici_0(line + i));
	return (1);
}

int ft_apici_0(char *line)
{
	int i;
	int	ap[2];
	
	i = ft_store_apici(ap, line);
	if ((ap[0] == 1 && ap[1] == 1) || (ap[0] == 2 && ap[1] == 2))
		return (ft_apici_0(line + i));
	else if (ap[0] == 2 && ap[1] == 1)
		return (ft_apici_1(line + i));
	else if (ap[0] == 1 && ap[1] == 2)
		return (ft_apici_2(line + i));
	return (0);
}

int init_parsing(char *line)
{
	if (solo_spazi(line))
		return (-1);
	if (ft_apici_pari(line))
		return (1);
	if (ft_apici_0(line))
		return (1);
	return (0);
}
