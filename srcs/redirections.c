#include "../includes/minishell.h"

int ft_redirect_maggiore(t_token *token)
{
    return (1);
}

int ft_redirect_pipe(t_token *token)
{
    t_token *primo;
    t_token *secondo;
    int fd[2];

    primo = token->prec;
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
        int x;

        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Got from child%d",y);
    }
}

int ft_redirect_minore(t_token *token)
{

    return (1);

    
}

int ft_redirect_dmaggiore(t_token *token)
{
    return (1);

}

int ft_redirect_dminore(t_token *token)
{

    return (1);
}
    
