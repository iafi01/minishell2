/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:18:55 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/12 16:43:10 by lmizzoni         ###   ########.fr       */
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
