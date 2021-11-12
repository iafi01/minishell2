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

void	add_list_loop(char ***dollar, int *i, char *val, char **tmp)
{
	char	*trash[2];
	int		k;

	*i = -1;
	k = count_words(val, '$');
	*dollar = ft_split(val, '$');
	while (++(*i) < k)
	{
		trash[1] = ft_alpha_give((*dollar)[*i]);
		if (getenv(trash[1]))
		{
			trash[0] = ft_strjoin(*tmp, getenv(trash[1]));
			free(*tmp);
			*tmp = trash[0];
			free(trash[1]);
			trash[1] = ft_symbols_give((*dollar)[*i]);
			if (trash[1] != NULL)
			{
				trash[0] = ft_strjoin(*tmp, trash[1]);
				free(trash[1]);
				free(*tmp);
				*tmp = trash[0];
			}
		}
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
	else if (!ft_strncmp(val, "$?", 2))
		list->next = ft_token_new(type, ft_strjoin(ft_itoa(g_glbl.ret), &val[2]),
			apici, list);
	else
		list->next = ft_token_new(type, val, apici, list);
	free(tmp);
	return (0);
}

void	end_echo(int *flag, int fd, t_global *global)
{
	if (*flag == 0)
		write(fd, "\n", 1);
	global->ret = 0;
}
