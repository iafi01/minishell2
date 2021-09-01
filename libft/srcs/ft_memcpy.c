/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:04:04 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/11 17:30:06 by lmizzoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*sd;
	char		*sr;

	sd = dst;
	sr = (void *)src;
	i = 0;
	while (i < n)
	{
		sd[i] = sr[i];
		i++;
	}
	return (dst);
}
