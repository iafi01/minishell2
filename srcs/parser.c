#include "../includes/minishell.h"

int ft_is_command(enum e_type i)
{
    if (i == CM_ECHO || i == CM_CD || i == CM_PWD || i == CM_EXP \
     || i == CM_UNS || i == CM_ENV || i == CM_EXIT)
        return (1);
    return (0);
}

enum e_type check_tokens_valid(t_token *token)
{
    if (token->next)
        token = token->next;
    while (token)
    {
        if (token->e_type != TK_ID && !ft_is_command(token->e_type))
            if (token->e_type == TK_PIPE || token->e_type == TK_GREATER \
             || token->e_type == TK_LOWER || token->e_type == TK_DGREA || token->e_type == TK_DLOW)
                if (token->prec->e_type != TK_ID || token->next->e_type != TK_ID)
                    return (0);
        token = token->next;
    }
    return (1);
}

int ft_parsing(t_global *global)
{
    t_token *tmp;
    t_token *token;

    if (global->token->next)
        token = global->token->next;
    else
        return (0);
    tmp = ft_find_end(token);
    if (tmp && cerca_token(tmp, TK_ID) != 1 && !ft_is_command(tmp->e_type))
        return (0);
    if (!check_tokens_valid(token))
        return (0);
    if (token->e_type == CM_PWD)
        ft_pwd();
    if (token->e_type == CM_ENV)
        ft_env(global);
    if (token->e_type == CM_CD)
        ft_cd(global->token->next);
    return (1);
}
