/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:07:51 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 01:07:53 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_listlen(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

int	ft_lstlen(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**list_to_arr(t_token *token)
{
	char	**arg;
	int		i;

	i = 0;
	arg = (char **)ft_malloc(sizeof(char *) * ft_listlen(token));
	while (token)
	{
		arg[i++] = token->val;
		token = token->next;
	}
	arg[i] = NULL;
	return (arg);
}

char	**lst_to_arr(t_list *list)
{
	char	**arg;
	int		i;

	i = 0;
	arg = (char **)ft_malloc(sizeof(char *) * ft_lstlen(list));
	while (list)
	{
		arg[i++] = list->content;
		list = list->next;
	}
	arg[i] = NULL;
	return (arg);
}
