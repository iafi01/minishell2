#include "../includes/minishell.h"

int ft_redirect_pipe(t_global *global, t_command *cmd)
{
    t_command *primo;
    t_command *secondo;
    int fd[2];
    int fd2[2];
    pid_t   id;

    // gdi-lore primo = ft_first_cmd(cmd);
    primo = cmd; // gdi-lore
    secondo = cmd->next;
    //printf("%s %s\n", primo->val, secondo->val);
    if (!primo || !secondo)
        return (0);
    if (pipe(fd) == -1)
    {
        ft_print_error("Error pipe\n");
        return (1);
    }
    id = fork();
    if (id < 0)
    {
        ft_print_error("Error fork\n");
        return (1);
    }
    if (id == 0) // processo figlio
    {
        if (dup2(fd[1], STDOUT_FILENO) == -1)
        {
            ft_print_error("Error11\n");
            free(cmd);      // lista di comandi, occhio
            exit (-1);
        }
        close(fd[0]);
        close(fd[1]);
        ft_exe_one(global, cmd);
        free(cmd);          // lista di comandi, occhio
        exit(0);
    }
    else // processo padre
    {
    //    wait(0);
        pipe(fd2);
        if (dup2(STDIN_FILENO, fd2[0]) == -1)
        {
            ft_print_error("Error11\n");
            free(cmd);      // lista di comandi, occhio
            exit (-1);
        }
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            ft_print_error("Error11\n");
            free(cmd);      // lista di comandi, occhio
            exit (-1);
        }
        close(fd[1]);
        close(fd[0]);
        ft_exe_commands(global, cmd->next);
        if (dup2(fd2[0], STDIN_FILENO) == -1)
        {
            ft_print_error("Error11\n");
            free(cmd);      // lista di comandi, occhio
            exit (-1);
        }
        close(fd2[1]);
        waitpid(id, NULL, 0);
    }
    return (0);
}