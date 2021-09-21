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
    /*ERRif (!check_tokens_valid(token))
        return (0);*/
    if (ft_token_priority(global, token) < 0)
        return (0);
    else if (exec_build_in(global, token, 1))
        return (0);
    return (1);
}

int exec_build_in(t_global *global, t_token *token, int fd)
{
    int i;

    i = 1;
    if (token->e_type == CM_ECHO)
        i = ft_echo(global, fd);
    if (token->e_type == CM_ENV)
        i = ft_env(global, fd);
    if (token->e_type == CM_CD)
        i = ft_cd(global->token->next);
    if (token->e_type == CM_EXP)
        i = ft_export(global, fd);
    if (token->e_type == CM_PWD)
        i = ft_pwd(fd);
    if (token->e_type == CM_UNS)
        i = ft_unset(global);
    if (token->e_type == CM_EXIT)
        return (0);
    if (token->e_type == TK_ID)
        execve(find_path(global->envp, token->val), list_to_arr(token) ,global->envp);
    return (i);
}

void    sub_var(t_token *list)
{
	while (list != NULL)
	{
        if (list->e_type == TK_ID && list->val[0] == '$')
		{
			free(list->val);
		}
		list = list->next;
	}
}
