#include "../includes/minishell.h"

t_token	*init_token(int type, char *val)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->val = val;
	return (token);
}

int	is_token(char *c)
{
	if (*(c+1) && (!ft_strncmp(c, ">>", 2) || !ft_strncmp(c, "<<", 2)))
		return (2);
	if (*c == '>' || *c == '<' || *c == '|')
		return (1);
	return (0);
}

int	is_token_type(int i)
{
	if (i == TK_LOWER || i == TK_PIPE || i == TK_GREATER || \
	 i == TK_DGREA || i == TK_DLOW || i == TK_PIPE)
		return (1);
	return (0);
}

t_token	*ft_token_new(t_type token, char *val, int apici, t_token *prec)
{
	t_token	*lnew;

	lnew = (t_token *)malloc(sizeof(t_token));
	lnew->prec = prec;
	lnew->e_type = token;
	lnew->val = val;
	lnew->apici = apici;
	lnew->next = NULL;
	return (lnew);
}

void	ft_free_list(t_token *list)
{
	t_token	*first;
	t_token	*next;

	if (!list || list->next == NULL)
		return ;
	first = list;
	list = list->next;
	while (list->next != NULL)
	{
		next = list->next;
		if (list->e_type == TK_ID)
			free(list->val);
		free(list);
		list = next;
	}
	list = first;
	list->next = NULL;
}

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
	else
		list->next = ft_token_new(type, val, apici, prec);
	if (list->next)
		return (1);
	return (0);
}

int ft_token_priority(t_token *token)
{
	int i;

	i = 0;
	while (token)
    {
        if (token->e_type == TK_GREATER)
			i = ft_redirect_maggiore(token);
		else if (token->e_type == TK_DGREA)
			i = ft_redirect_dmaggiore(token);
        else if (token->e_type == TK_LOWER)
			i = ft_redirect_minore(token);
		else if(token->e_type == TK_DLOW)
			i = ft_redirect_dminore(token);
		else if (token->e_type == TK_PIPE)
			i = ft_redirect_pipe(token);
		if (i < 0)
			return (-1);
        token = token->next;
    }
	return (0);
}
