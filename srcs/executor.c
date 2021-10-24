#include "../includes/minishell.h"

int    ft_exe_one(t_global * global, t_command *coms)
{
    int fdi;
    int fdo;
    int ret;

    fdi = STDIN_FILENO;
    fdo = STDOUT_FILENO;
    ft_redirect(coms, &fdi, &fdo);
    ret = ft_exec_build_in(global, coms, fdi, fdo);
    return (ret);
}

void    ft_exe_commands(t_global *global, t_command * simple_coms)
{
    if (get_size_simple_com(simple_coms) > 1)
        ft_redirect_pipe(global, simple_coms);
    else
        ft_exe_one(global, simple_coms);
}

int ft_exec_build_in(t_global *global, t_command *cmd, int fdi, int fdo)
{
    int     i;
    char    **arr;
    pid_t   pid;
    
    i = 0;
    if (cmd->cmd == NULL)
        return (i);
    if (!ft_strncmp(str_tolower(cmd->cmd), "echo", 5))
        i = ft_echo(global, fdo);
    else if (!ft_strncmp(str_tolower(cmd->cmd), "env", 4))
        i = ft_env(global, fdo);
    else if (!ft_strncmp(cmd->cmd, "cd", 3))
        i = ft_cd(global->token->next);
    else if (!ft_strncmp(cmd->cmd, "export", 7))
        i = ft_export(global, fdo);
    else if (!ft_strncmp(str_tolower(cmd->cmd), "pwd", 4))
        i = ft_pwd(fdo);
    else if (!ft_strncmp(cmd->cmd, "unset", 6))
        i = ft_unset(global);
    // if (cmd->cmd == TK_ID && ft_split(token->val, '='))
    // {
    //     spl = ft_split(token->val, '=');
    //     if (cerca_variabile(spl[0]) != NULL)
    //         i = sostitute_set(global, 0);
    //     return (0);
    // }
    else if (!ft_strncmp(cmd->cmd, "exit", 5))
        ft_exit(global);
    // else
    // {
    //     if (fork() == 0)
    //     {
    //         spl = get_options(token);
    //         execve(find_path(global->envp, spl[0]), spl ,NULL);
    //     }
    // }
    else
    {
        pid = fork();
        glbl.pid = pid;
        if (pid < 0)
            perror("error");
        if (pid == 0)
        {
            if (fdi != 0)
                dup2(fdi, 0);
            if (fdo != 1)
                dup2(fdo, 1);
            ft_lstadd_front(&cmd->par, ft_lstnew(cmd->cmd));
            arr = lst_to_arr(cmd->par);
            execve(find_path(global->envp, cmd->cmd), arr , global->envp);
            close(0);
            close(1);
            exit(0);
		}
    }
    wait(0);
    return (i);
}