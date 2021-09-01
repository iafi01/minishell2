#include "libft.h"

int	ft_str_end(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	if (i < j)
		return (0);
	while (str[i] && end[j])
	{
		if (str[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
