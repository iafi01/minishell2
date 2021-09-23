#include "../includes/minishell.h"

int ft_listlen(t_token *token)
{
    int i;

    i = 0;
    while (token)
    {
        i++;
        token = token->next;
    }
    return (i);
}

char **list_to_arr(t_token *token)
{
    char **arg;
    int i;

    i = 0;
    arg = malloc(sizeof(char *) * ft_listlen(token));
    while (token)
    {
        arg[i++] = token->val;
        //printf ("%s\n", arg[i - 1]);
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

