#include "../includes/minishell.h"

char	*cerca_variabile(char *line)
{
    char string[32767];
    int i;

    i = 0;
    while (line[i])
    {
        string[i] = line[i];
        if (getenv(string))
            return (getenv(string));
        i++;
    }
    return (NULL);
}

char	*ft_getenv(t_global *global, char *var)
{
	char	*variable;
	int i;

	i = 0;
	while (ft_strncmp(global->envp[i], var, ft_strlen(var)) && global->envp[i + 1])
		i++;
	if (ft_strncmp(global->envp[i], var, ft_strlen(var)) == 0)
	{
		variable = ft_strdup(global->envp[i]);
		return (variable);
	}
	printf("error env var \n");
	return ((char *)NULL);
}

int	count_var(char* line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '/')
			return (i);
		i++;
	}
	return (ft_strlen(line));
}

int cerca_token(t_token *token, enum e_type type)
{
    if (token->next)
		token = token->next;
	while (token != NULL)
	{
		if (token->e_type == type)
            return (1);
		token = token->next;
	}
    return (0);
}

t_token	*ft_find_end(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

int	store_token(t_token *list, char *t)
{
	t_token	*end;

	end = ft_find_end(list);
	if (!ft_strncmp(t, ">>", 2))
		return (ft_add_list(list, TK_DGREA, NULL, 0));
	else if (!ft_strncmp(t, "<<", 2))
		return (ft_add_list(list, TK_DLOW, NULL, 0));
	else if (*t == '>')
		return (ft_add_list(list, TK_GREATER, NULL, 0));
	else if (*t == '<')
		return (ft_add_list(list, TK_LOWER, NULL, 0));
	else if (*t == '|')
		return (ft_add_list(list, TK_PIPE, NULL, 0));
	else if (*t == '>')
		return (ft_add_list(list, TK_GREATER, NULL, 0));
	else if (*t == '=' && end->prec->e_type == CM_EXP)
		return (ft_add_list(list, TK_EQ, NULL, 0));
	return (0);
}
