/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:23:04 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/12 14:24:23 by lmizzoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destsize;
	size_t	i;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	destsize = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && ((destsize + 1) < size))
	{
		dst[destsize] = src[i];
		destsize++;
		i++;
	}
	dst[destsize] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
