/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:05:51 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/13 14:14:57 by lmizzoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;
	char	*start;

	cpy = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!cpy)
		return (0);
	start = cpy;
	while (*src)
		*(cpy++) = *(src++);
	*cpy = '\0';
	return (start);
}
