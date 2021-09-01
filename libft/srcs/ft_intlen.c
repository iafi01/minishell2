#include "libft.h"

size_t	ft_intlen(intmax_t n)
{
	size_t	len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
