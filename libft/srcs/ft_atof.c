/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:13:25 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 02:13:27 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
float		ft_atof(char *str)
{
	float	atof;
	int		atoi;
	int		i;
	int		fac;

	fac = 1;
	atof = 0;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	str[i] == '-' ? fac = -1 : 0;
	atoi = ft_atoi(str);
	i = ft_intlen(atoi);
	fac == -1 ? i++ : 0;
	if (str[i] != '.')
		return (atoi);
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fac *= 10;
		atof = atof * 10 + str[i] - 48;
		i++;
	}
	atof = atof / fac;
	return (atoi + atof);
}
*/

//function that allocates a pointer of size size and prints its pointer address
void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	// printf("%p\n", ptr);

	return (ptr);
}

static int	ft_first(char *str, int i, int fac)
{
	if (str[i] == '-')
		return (-1);
	return (fac);
}

static int	ft_second(int fac, int i)
{
	if (fac == -1)
		return (++i);
	return (i);
}

float	ft_atof(char *str)
{
	float	atof;
	int		atoi;
	int		i;
	int		fac;

	fac = 1;
	atof = 0;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	fac = ft_first(str, i, fac);
	atoi = ft_atoi(str);
	i = ft_intlen(atoi);
	i = ft_second(fac, i);
	if (str[i] != '.')
		return (atoi);
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fac *= 10;
		atof = atof * 10 + str[i] - 48;
		i++;
	}
	atof = atof / fac;
	return (atoi + atof);
}
