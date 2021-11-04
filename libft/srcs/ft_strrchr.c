/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:59:31 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 02:59:32 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*new;

	new = 0;
	while (*s)
	{
		if (*s == (char)c)
			new = (char *)s;
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (new);
}
