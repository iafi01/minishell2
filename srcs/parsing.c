/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:35:27 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 22:35:29 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strchr2(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (1);
	return (0);
}

int	apici_if(int *i, char *line)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == 34)
		{
			if (line[*i + 1])
				return (ft_apici_invers(&line[*i + 1]));
			else
				return (0);
		}
		(*i)++;
	}
	return (1);
}

int	apici_else(int *i, char *line)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == 39)
		{
			if (line[*i + 1])
				return (ft_apici_invers(&line[*i + 1]));
			else
				return (0);
		}
		(*i)++;
	}
	return (1);
}

int	ft_apici_invers(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			return (apici_if(&i, line));
		else if (line[i] == 39)
			return (apici_else(&i, line));
	}
	if (count == 1)
		return (1);
	return (0);
}

int	init_parsing(char *line)
{
	if (solo_spazi(line))
		return (-1);
	if (ft_apici_invers(line))
		return (1);
	return (0);
}
