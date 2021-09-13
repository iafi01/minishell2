#include "../includes/minishell.h"

char **list_to_arr(t_token *token)
{
    char **arg;
    int i;

    i = 0;
    if (!token->next)
        return (NULL);
    token = token->next;
    while (token)
    {
        arg[i++] = token->val;
        token = token->next;
    }
    arg[i] = '\0';
    return (arg);
}

t_token *arr_to_list(char **arg)
{
    t_token *token;
    int i;

    i = 0;
    token = ft_token_new(TK_ID, NULL, 0, NULL);
    while (arg[i++])
        ft_add_list(token, TK_ID, arg[i], 0);
    return (token);
}

