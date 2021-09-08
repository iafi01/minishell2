#include "../includes/minishell.h"

enum e_type check_tokens_valid(t_token *token)
{
    if (token->next)
        token = token->next;
    while (token)
    {
        if (token->e_type != TK_ID)
            if (token->e_type == TK_PIPE || token->e_type == TK_GREATER \
             || token->e_type == TK_LOWER || token->e_type == TK_DGREA || token->e_type == TK_DLOW)
                if (token->prec && token->next)
                    return (0);
        token = token->next;
    }
    return (1);
}

int ft_parsing(t_token *token)
{
    t_token *tmp;

    tmp = ft_find_end(token);
    if (tmp && cerca_token(tmp, TK_ID) != 1)
        return (0);
    if (!check_tokens_valid(token))
        return (0);
    return (1);
}
