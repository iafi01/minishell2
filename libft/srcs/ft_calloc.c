/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:17:15 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 02:17:17 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**    nitems : num. of elem. to be allocated.
**    size   : size of the elements.
*/

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t		size_tot;
	void		*dst;

	size_tot = size * nitems;
	dst = ft_malloc(size_tot);
	if (!dst)
		return (0);
	ft_memset(dst, 0, size_tot);
	return (dst);
}
