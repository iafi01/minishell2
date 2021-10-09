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

/*int	ft_store_apici(int *ap, char *line)
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
}*/
/*
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
}*/

int ft_strchr2(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (1);
	return (0);
}

/*int ft_apici_inv(char *line)
{
	int i;
	char *copy;
	char c;
	char *ret;

	int j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			c = line[i];
			if (ft_strchr2(&line[i + 1], c) == 1)
			{
				i++;
				while (line[i] != c)
				{
					copy[j] = line[i];
					j++;
					i++;
				}
			}
		}

		ft_strjoin(ret, copy);
		i++;
	}
}*/

int ft_apici_invers(char *line)
{
	int i;
	char c;
	int count = 0;

	i = -1;
	//printf("%s\n", line);
	while (line[++i])
	{
		if (line[i] == 34)
		{
			i++;
			while (line[i])
			{
				if (line[i] == 34)
					if (line[i + 1])
						return (ft_apici_invers(&line[i + 1]));
					else
						return (0);
				i++;
			}
			return (1);
		}
		else if (line[i] == 39)
		{
			i++;
			while (line[i])
			{
				if (line[i] == 39)
					if (line[i + 1])
						return (ft_apici_invers(&line[i + 1]));
					else
						return (0);
				i++;
			}
			return (1);
		}
	}
	if (count == 1)
		return (1);
	return (0);
}

int init_parsing(char *line)
{
	if (solo_spazi(line))
		return (-1);
	if (ft_apici_invers(line))
		return (1);
	return (0);
}
