/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:56:00 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 02:56:01 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;
	char	*start;

	if (!src)
		return (NULL);
	cpy = (char *)ft_malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!cpy)
		return (0);
	start = cpy;
	while (*src)
		*(cpy++) = *(src++);
	*cpy = '\0';
	return (start);
}
