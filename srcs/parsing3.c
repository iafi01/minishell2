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
	if (val[0] == '~')
		list->next = ft_token_new(type, getenv("HOME"), apici, prec);
	else if (val[0] == '$')
	{
		dollar = ft_split(val, '$');
		while (dollar[i])
		{
			if (getenv(dollar[i]))
				tmp = ft_strjoin(tmp ,getenv(dollar[i]));
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
