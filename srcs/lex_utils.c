/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:05:29 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 20:05:31 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	apici_loop(char *line, int *i, char *s, char **tmp)
{
	char	*trash;

	if (line[*i] == 32)
		return (1);
	if (line[*i] == 39 || line[*i] == 34)
	{
		if (line[*i + 1])
			(*i)++;
		else
			return (1);
	}
	s[0] = line[*i];
	trash = ft_strjoin(*tmp, s);
	free(*tmp);
	*tmp = trash;
	return (0);
}

char	*ft_apici_split(char *line)
{
	int		i;
	int		apici;
	char	*tmp;
	char	s[2];

	s[1] = '\0';
	apici = 0;
	i = -1;
	tmp = calloc(30, sizeof(char));
	if (line[i] == 39)
		apici = 1;
	else if (line[i] == 34)
		apici = 2;
	while (line[++i])
		if (apici_loop(line, &i, s, &tmp))
			break ;
	i++;
	return (tmp);
}
