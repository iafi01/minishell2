/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:11:19 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 23:11:20 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(int type, char *val)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->val = val;
	return (token);
}

int	is_token(char *c)
{
	if (*(c + 1) && (!ft_strncmp(c, ">>", 2) || !ft_strncmp(c, "<<", 2)))
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

	lnew = (t_token *)ft_malloc(sizeof(t_token));
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

	if (!list)
		return ;
	first = list;
	next = list->next;
	free(list);
	list = next;
	while (list != NULL)
	{
		next = list->next;
		if (list->e_type == TK_ID)
			free(list->val);
		free(list);
		list = next;
	}
	list = first;
}
