#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;
    int     n;

    n = ft_strlen(str1);
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
    if ((unsigned char)(str1[i]) > (unsigned char)(str2[i]))
        return (1);
	return (-1);
}