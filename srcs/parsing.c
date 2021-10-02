#include "../includes/minishell.h"

char *skip_spaces(char *str)
{
	int i;
	
	i = 0;
	while (str[i] == 32)
		str++;
	return (str);
}

int control_apici(int s_apici, int d_apici)
{
	if (s_apici % 2 != 0 || d_apici % 2 != 0)
		return (0);
	return (1);
}

int check_apici(char *line)
{
	int i;
	int s_apici;
	int d_apici;

	i = 0;
	s_apici = 0;
	d_apici = 0;
	while (line[i] != 0)
	{
		if (line[i] == 34)
			d_apici += 1;
		if (line[i] == 39)
			s_apici += 1;
		i++;
	}
	if (!control_apici(s_apici, d_apici))
		return (0);
	return (1);
}

int check_inv(char *line)
{
	int i = -1;
	int fapice = 0;

	fapice = first_apice(line);
	while (line[i++])
	{
		if (line[i] == 34 || line[i] == 39)
			break;
	}
	while (line[i++])
	{
		if (line[i] == 34 && fapice == 1)
		{
			while (line[i++])
			{
				if (line[i] == 34)
					return (1);
			}
			return (0);
		}
		else if (line[i] == 39 && fapice == 2)
		{
			while (line[i++])
			{
				if (line[i] == 39)
					return (1);
			}
			return (0);
		}
	}
	return (0);
}

int init_parsing(char *line)
{
	if (solo_spazi(line))
		return (-1);
	if (!check_apici(line))
		return (1);
	if (!check_inv(line))
		return (1);
	return (0);
}
