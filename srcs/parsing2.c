/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:46:26 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 22:46:28 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	solo_spazi(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\t' && line[i] != '\n' && line[i] != '\v'   
			&& line[i] != '\f' && line[i] != '\r' && line[i] != 32)
			return (0);
        i++;
	}
	return (1);
}

char	*ft_alpha_give(char *s)
{
	char	*new;
	int		i;

	i = 0;
	new = calloc(sizeof(char), ft_strlen(s));
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '$')
			new[i] = s[i];
		else
			return (new);
		i++;
	}
	if (new[0])
		return (new);
	return (NULL);
}

char	*ft_symbols_give(char *s)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new = calloc(sizeof(char), ft_strlen(s));
	while (s[i] && s[i] != '$')
	{
		if (!ft_isalpha(s[i]))
			new[j++] = s[i];
		i++;
	}
	if (new[0])
		return (new);
	return (NULL);
}