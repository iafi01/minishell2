#include "../includes/minishell.h"

int ft_parsing(t_token *token)
{
    t_token *tmp;

    tmp = ft_find_end(token);
    if (tmp && cerca_token(tmp, TK_ID) != 1)
        return (0);
    return (1);
}

static void	ft_set_cmd_final(t_token *list)
{
	while (list != NULL)
	{
		if (list->e_type > 9 && list->val != NULL)
		{
			free(list->val);
			list->val = NULL;
		}
		list = list->next;
	}
	return ;
}

void	ft_check_doubles(t_token *list)
{
	t_type	token;
	t_token	*first;

	first = list;
	if (list)
	{
		token = list->e_type;
		list = list->next;
	}
	while (list != NULL)
	{
		printf("\n%d->%d\n", token, list->e_type);
		if (token == list->e_type)
			list->e_type = TK_ID;
		else if (token != list->e_type
			&& list->e_type > 9)
		{
			free(list->val);
			list->val = NULL;
		}
		printf("%d->%d\n", token, list->e_type);
		token = list->e_type;
		printf("%d->%d\n", token, list->e_type);
		list = list->next;
	}
	ft_set_cmd_final(first);
	return ;
}