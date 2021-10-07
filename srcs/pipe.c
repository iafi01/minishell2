#include "minishell.h"

int ft_redirect_pipe(t_global *global, t_command *cmd)
{
    t_command *primo;
    t_command *secondo;
    int fd[2];

    primo = ft_first_cmd(cmd);
    secondo = cmd->next;
    //printf("%s %s\n", primo->val, secondo->val);
    if (!primo || !secondo)
        return (0);
    if (pipe(fd) == -1)
    {
        printf("Error pipe");
        return (1);
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
        {
            write(2, "Error11\n", 30);
            return (0);
        }
        close(fd[1]);
        char **str;

        str = (char **)malloc(sizeof(char *) * 5);
        str[0] = "ls";
        str[1] = "-l";
        if (execve(find_path(global->envp, "ls"), str, global->envp) == -1)
        {
            write(2, strerror(errno), 9);
            return (0);
        }
    }
    else
    {
        wait(0);
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            write(2, "Error21\n", 30);
            return (0);
        }
        close(fd[0]);
        char **str2;
        str2 = (char **)malloc(sizeof(char *) * 5);
        str2[0] = "wc";
        str2[1] = "-l";
        if (execve(find_path(global->envp, "wc"), str2, global->envp) == -1)
        {
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            return (0);
        }
    }
    return (0);
}