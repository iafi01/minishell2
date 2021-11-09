/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:15:05 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 01:15:07 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cerca_variabile(char *line)
{
	char	string[32767];
	int		i;

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

void	write_b(int n)
{
	while (n > 0)
	{
		printf("\b");
		n--;
	}
	return ;
}

int	ft_get_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	**ft_copy_env(char **envp)
{
	int		s;
	int		i;
	char	**res;

	s = ft_get_size(envp);
	i = 0;
	res = (char **)ft_malloc(sizeof(char *) * s);
	while (i < s)
	{
		res[i] = envp[i];
		i++;
	}
	return (res);
}

void	stringa_unica_aux(char *line, int *j, char **tmp)
{
	char	*trash;
	char	*trash2;

	if (line[j[1]] == 34)
	{
		trash2 = ft_stringa_unica(line + j[1], j, 2);
		trash = ft_strjoin(*tmp, trash2);
		free(*tmp);
		free(trash2);
		*tmp = trash;
	}
	else if (line[j[1]] == 39)
	{
		trash2 = ft_stringa_unica(line + j[1] + 1, j, 1);
		trash = ft_strjoin(*tmp, trash2);
		free(trash2);
		free(*tmp);
		*tmp = trash;
	}
}
