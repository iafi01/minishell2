/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:52:38 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/13 14:14:49 by lmizzoni         ###   ########.fr       */
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
	dst = malloc(size_tot);
	if (!dst)
		return (0);
	ft_memset(dst, 0, size_tot);
	return (dst);
}
