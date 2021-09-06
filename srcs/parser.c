#include "../includes/minishell.h"

int ft_parsing(t_token *token)
{
    t_token *tmp;

    tmp = ft_find_end(token);
    if (tmp && cerca_token(tmp, TK_ID) != 1)
        return (0);
    return (1);
}
