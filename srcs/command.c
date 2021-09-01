#include "../includes/minishell.h"

int ft_tree(t_global *global)
{
    if (!ft_strncmp(global->line[0], "echo", 4) || !ft_strncmp(global->line[0], "ECHO", 4))
        ft_echo(global);
    else if (!ft_strncmp(global->line[0], "env", 3) || !ft_strncmp(global->line[0], "ENV", 3))
        ft_env(global);
    else if (!ft_strncmp(global->line[0], "pwd", 3) || !ft_strncmp(global->line[0], "PWD", 3))
        ft_pwd();
    if (!ft_strncmp(global->line[0], "echo ", 5) || !ft_strncmp(global->line[0], "ECHO ", 5))
        ft_echo(global);
    else if (!ft_strncmp(global->line[0], "env", 4) || !ft_strncmp(global->line[0], "ENV", 4))
        ft_env(global);
    else if (!ft_strncmp(global->line[0], "pwd", 4) || !ft_strncmp(global->line[0], "PWD", 4))
        ft_pwd();
    else if (!ft_strncmp(global->line[0], "exit", 4))
        return (0);
    else if (!ft_strncmp(global->line[0], "export", 6))
        ft_export(global);
    else if (!ft_strncmp(global->line[0], "unset", 5))
        unset(global);
    else if (!ft_strncmp(global->line[0], "cd", 2))
        ft_cd(global);
    else
        printf("Comando sconosciuto\n"); // execve da addare
    return (1);
}