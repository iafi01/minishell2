#include "libft.h"

void	ft_str_delete(char **s)
{
	free(*s);
	*s = NULL;
}
