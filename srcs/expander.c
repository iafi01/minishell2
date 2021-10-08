#include "../includes/minishell.h"

void ft_expand(t_global *global)
{
    t_token *token;
    t_token *nuovo;
    t_list  *list;

    nuovo = ft_token_new(TK_ID, NULL, 0, NULL);
    list = nuovo;
    token = global->token;
    while (token)
    {
        printf("token%s\n", token->val);
        ft_expander(token, token->e_type, token->val, token->apici, nuovo);
        nuovo = nuovo->next;
        token = token->next;
    }
    global->token = list->next;
}

void ft_expander(t_token *list, t_type type, char *val, int apici, t_token *nuovo)
{
    t_token *prec;
	char **dollar;
	int i;
	char *tmp;

    if (val != NULL && val[0] == '~')
        nuovo->next = ft_token_new(type, getenv("HOME"), apici, prec);
    else if (val != NULL && val[0] == '$')
    {
        dollar = ft_split(val, '$');
        while (dollar[i])
        {
            if (getenv(ft_alpha_give(dollar[i])))
            {
                tmp = ft_strjoin(tmp ,getenv(ft_alpha_give(dollar[i])));
                if (ft_symbols_give(dollar[i]))
                    tmp = ft_strjoin(tmp , ft_symbols_give(dollar[i]));
            }
            i++;
        }
        if (tmp)
            nuovo->next = ft_token_new(type, tmp, apici, prec);
    }
    else
        nuovo->next = ft_token_new(type, val, apici, prec);
}