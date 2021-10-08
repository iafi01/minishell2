#include "../includes/minishell.h"

void ft_expander(t_token *list, t_type type, char *val, int apici)
{
    t_token *prec;
	char **dollar;
	int i;
	char *tmp;

    if (val != NULL && val[0] == '~')
            list->next = ft_token_new(type, getenv("HOME"), apici, prec);
        else if (val != NULL && val[0] == '$' /*&& val[1] != '?'*/)
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
                list->next = ft_token_new(type, tmp, apici, prec);
        }
}