#include "../includes/minishell.h"

char *ft_alpha_give(char *s)
{
	char *new;
	int i;

	i = 0;
	new = calloc(sizeof(char) , ft_strlen(s));
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '$')
			new[i] = s[i];
		else
			return (new);
		i++;
	}
	if (new[0])
		return (new);
	return (NULL);
}

char *ft_symbols_give(char *s)
{
	char *new;
	int i;
	int j;

	j = 0;
	i = 0;
	new = calloc(sizeof(char) , ft_strlen(s));
	while (s[i] && s[i] != '$')
	{
		if (!ft_isalpha(s[i]))
			new[j++] = s[i];
		i++;
	}
	if (new[0])
		return (new);
	return (NULL);
}

int	ft_add_list(t_token *list, t_type type, char *val, int apici)
{
	t_token *prec;
	char **dollar;
	int i;
	char *tmp;

	i = 0;
	tmp = calloc(30, sizeof(char));
	list = ft_find_end(list);
	prec = list;
	if (val != NULL && val[0] == '~')
	{
		tmp = getenv("HOME");
		if (++val)
			tmp = ft_strjoin(tmp, val);
		list->next = ft_token_new(type, tmp, apici, prec);
	}
	else if (val != NULL && val[0] == '$' && val[1] && apici != 1)
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
	else
		list->next = ft_token_new(type, val, apici, prec);
	if (list->next)
		return (1);
	return (0);
}

// int ft_token_priority(t_global *global, t_token *token)
// {
// 	int i;

// 	i = 0;

// 	while (token)
//     {
//         if (token->e_type == TK_GREATER)
// 			i = ft_redirect_maggiore(global, token);
// 		else if (token->e_type == TK_DGREA)
// 			i = ft_redirect_dmaggiore(global, token);
//         else if (token->e_type == TK_LOWER)
// 			i = ft_redirect_minore(global, token);
// 		else if(token->e_type == TK_DLOW)
// 			i = ft_redirect_dminore(global, token);
// 		else if (token->e_type == TK_PIPE)
// 			i = ft_redirect_pipe(global, token);
// 		if (i < 0)
// 			return (-1);
//         token = token->next;
//     }
// 	return (0);
// }

int ft_is_command(enum e_type i)
{
    if (i == CM_ECHO || i == CM_CD || i == CM_PWD || i == CM_EXP \
     || i == CM_UNS || i == CM_ENV || i == CM_EXIT || i ==  CM_CMD)
        return (1);
    return (0);
}
