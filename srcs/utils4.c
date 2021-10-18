#include "../includes/minishell.h"

char	**get_options(t_token *token)
{
	char	**str;
	int		size;
	int		i;
	t_token *temp;

	i = 0;
	size = 1;
	if (!token)
		return (NULL);
	temp = token;
	if (token->next)
		temp = token->next;
	while(temp->e_type == CM_OPT && temp)
	{
		size++;
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	str = (char **)malloc(sizeof(char *) * size + 1);
	temp = token;
	while(i < size)
	{
		str[i] = ft_strdup(temp->val);
		temp = temp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

t_token *find_cmd(t_token *token)
{
	t_token *temp;

	temp = token;
	if (!temp || !temp->prec)
		return (NULL);
	temp = temp->prec;
	while (temp && temp->e_type != CM_CMD)
	{
		if (temp->e_type != CM_OPT)
			return (NULL);
		temp = temp->prec;
	}
	return (temp);
	
}

int		check_if_options(t_token *tkn, char *opt)
{
	if (!tkn->prec)
		return (0);
	if (opt && opt[0])
	{
		if (tkn->prec->e_type == CM_CMD)
			return(1);
		else if (tkn->prec->e_type == CM_OPT)
			return (1);
	}
	return (0);
}

int	check_if_cmd(t_token *tkn)
{
	static int i = 1;

	if (!tkn->prec)
		return (0);
	i++;
	if (tkn->prec->e_type == 5 || tkn->prec->e_type == 6)
		return (1);
	return(0);
}

int		is_path(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '/')
				return(1);
			i++;
		}
	}
	return (0);
}
