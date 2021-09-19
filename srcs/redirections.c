#include "../includes/minishell.h"

int ft_redirect_maggiore(t_token *token)
{
    return (1);
}

int ft_redirect_pipe(t_token *token)
{
    t_token *primo;
    t_token *secondo;
    //int fd[2];

    primo = token->prec;
    secondo = token->next;

    if (!primo || !secondo)
        return (0);
    
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
    
