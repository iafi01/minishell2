/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:55:08 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 02:55:10 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_end(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	if (i < j)
		return (0);
	while (str[i] && end[j])
	{
		if (str[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
