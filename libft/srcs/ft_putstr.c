#include "libft.h"

void	ft_putstr(char const *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}
