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

static void	add_list_loop(char ***dollar, int *i, char *val, char **tmp)
{
	char	*trash;
	char	*lezzo;

	*i = 0;
	*dollar = ft_split(val, '$');
	while (*dollar[*i])
	{
		lezzo = ft_alpha_give(*dollar[*i]);
		if (getenv(lezzo))
		{
			trash = ft_strjoin(*tmp, getenv(lezzo));
			free(*tmp);
			*tmp = trash;
			free(lezzo);
			lezzo = ft_symbols_give(*dollar[*i]);
			if (lezzo)
			{
				trash = ft_strjoin(*tmp, lezzo);
				free(lezzo);
				free(*tmp);
				*tmp = trash;
			}
		}
		(*i)++;
	}
}

static void	add_list_if(char **tmp, char **val)
{
	char	*trash;

	*tmp = getenv("HOME");
	if (++(*val))
	{
		trash = ft_strjoin(*tmp, *val);
		free(*tmp);
		*tmp = trash;
	}
}

int	ft_add_list(t_token *list, t_type type, char *val, int apici)
{
	char	**dollar;
	int		i;
	char	*tmp;

	tmp = ft_calloc(30, sizeof(char));
	list = ft_find_end(list);
	if (val != NULL && val[0] == '~')
	{
		add_list_if(&tmp, &val);
		list->next = ft_token_new(type, ft_strdup(tmp), apici, list);
		free(val);
	}
	else if (val != NULL && val[0] == '$'
		&& val[1] != '?' && val[1] && apici != 1)
	{
		add_list_loop(&dollar, &i, val, &tmp);
		list->next = ft_token_new(type, ft_strdup(tmp), apici, list);
		free(val);
		free(*dollar);
		free(dollar);
	}
	else
		list->next = ft_token_new(type, val, apici, list);
	free(tmp);
	return (0);
}
