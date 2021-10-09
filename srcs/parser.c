#include "../includes/minishell.h"

// int check_redirections(t_token *token)
// {
//     int i;

//     i = 0;
//     while (token)
//     {
//         if (is_token_type(token->e_type))
//         {
//             if (i == 0)
//             {
//                 i = 1;
//             }
//             else
//             {
//                 return (-1);
//             }
//         }  
//         else
//         {
//             i = 0;
//         }
//         token = token->next;
//     }
//     return (0);
// }

int ft_check_tokens(t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp)
    {
        if (is_token_type(tmp->e_type))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

// int ft_parsing(t_global *global)
// {
//     t_token *tmp;
//     t_token *token;

//     if (global->token->next)
//         token = global->token->next;
//     else
//         return (0);
//     tmp = ft_find_end(token);
//     //if (tmp && cerca_token(tmp, TK_ID) != 1 && !ft_is_command(tmp->e_type))
//     //    return (0);
//     /*ERRif (!check_tokens_valid(token))
//         return (0);*/
//     //controllare se due redirection sono attaccate
//     /*if (check_redirections(token) == -1);
//         return (0); */
//     if (ft_check_tokens(token) == 1)
//         if (ft_token_priority(global, token) < 0)
//             return (0);
//     if (ft_check_tokens(token) == 0)
//         if (exec_build_in(global, token, 1) < 0)
//             return (0);
//     return (1);
// }

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
