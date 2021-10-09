#include "../includes/minishell.h"

void    ft_print_error(char *str)
{
    write(2, str, ft_strlen(str));
}

size_t	get_size_simple_com(t_command *coms)
{
	size_t	count;

	count = 0;
	while (coms != NULL)
	{
		count++;
		coms = coms->next;
	}
	return (count);
}
