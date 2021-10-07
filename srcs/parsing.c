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

int init_parsing(char *line)
{
	if (solo_spazi(line))
		return (-1);
	// if (ft_check_apici(line))
	// 	return (1);
	return (0);
}
