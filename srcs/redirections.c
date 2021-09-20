#include "../includes/minishell.h"

int ft_redirect_maggiore(t_global *global, t_token *token)
{
    return (1);
}

t_token *ft_first_cmd(t_token *list)
{
    while (list->prec != NULL && !is_token_type(list->prec->e_type))
    {
        list = list->prec;
    }
    list = list->next;
    return (list);
}

int ft_redirect_pipe(t_global *global, t_token *token)
{
    t_token *primo;
    t_token *secondo;
    int fd[2];

    primo = ft_first_cmd(token);
    secondo = token->next;
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
        exec_build_in(global, primo, fd[1]);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char* y;
        read(fd[0], &y, sizeof(char*));
        close(fd[0]);
        printf("Got from child%s",y);
    }
}

int ft_redirect_minore(t_global *global, t_token *token)
{

    return (1);

    
}

int ft_redirect_dmaggiore(t_global *global, t_token *token)
{
    return (1);

}

int ft_redirect_dminore(t_global *global, t_token *token)
{

    return (1);
}
    
