/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:56:13 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 22:56:22 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_list_loop(char ***dollar, int *i, char *val, char *tmp)
{
	char	*trash;

	*i = 0;
	*dollar = ft_split(val, '$');
	while (*dollar[*i])
	{
		if (getenv(ft_alpha_give(*dollar[*i])))
		{
			trash = ft_strjoin(tmp, getenv(ft_alpha_give(*dollar[*i])));
			free(tmp);
			tmp = trash;
			if (ft_symbols_give(*dollar[*i]))
			{
				trash = ft_strjoin(tmp, ft_symbols_give(*dollar[*i]));
				free(tmp);
				tmp = trash;
			}
		}
		(*i)++;
	}
}

static void	add_list_if(char *tmp, char **val)
{
	tmp = getenv("HOME");
	if (++(*val))
		tmp = ft_strjoin(tmp, *val);
}

int	ft_add_list(t_token *list, t_type type, char *val, int apici)
{
	t_token	*prec;
	char	**dollar;
	int		i;
	char	*tmp;

	tmp = calloc(30, sizeof(char));
	list = ft_find_end(list);
	prec = list;
	if (val != NULL && val[0] == '~')
	{
		add_list_if(tmp, &val);
		list->next = ft_token_new(type, tmp, apici, prec);
	}
	else if (val != NULL && val[0] == '$'
		&& val[1] != '?' && val[1] && apici != 1)
	{
		add_list_loop(&dollar, &i, val, tmp);
		if (tmp)
			list->next = ft_token_new(type, tmp, apici, prec);
	}
	else
		list->next = ft_token_new(type, val, apici, prec);
	if (list->next)
		return (1);
	return (0);
}
