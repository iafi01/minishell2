#include "../includes/minishell.h"

char	*cerca_variabile(char *line)
{
    char string[32767];
    int i;

    i = 0;
    while (line[i])
    {
        string[i] = line[i];
        if (getenv(string))
            return (getenv(string));
        i++;
    }
    return (NULL);
}

int	count_var(char* line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '/')
			return (i);
		i++;
	}
	return (ft_strlen(line));
}