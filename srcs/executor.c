#include "../includes/minishell.h"

void    ft_exe_one(t_command *coms)
{
    coms = 0;
}

void    ft_exe_commands(t_global *global, t_command * simple_coms)
{
    if (get_size_simple_com(simple_coms) > 1)
        ft_redirect_pipe(global, simple_coms);
    else
        ft_exe_one(simple_coms);
}
