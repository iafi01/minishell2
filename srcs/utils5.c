/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:17:14 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 01:17:15 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

size_t	get_size_simple_com(t_command *coms)
{
	size_t	count;

	count = 0;
	while (coms != NULL)
	{
		count++;
		coms = coms->next;
	}
	return (count);
}

char	*str_tolower(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_strdup(str);
	while (ret[i])
	{
		if (ret[i] >= 'A' && ret[i] <= 'Z')
			ret[i] += 32;
		i++;
	}
	return (ret);
}

t_redirect	*ft_new_redirect(char *file, t_type red_type)
{
	t_redirect	*new;

	new = malloc(sizeof(new));
	if (new == NULL)
		return (NULL);
	new->file = ft_strdup(file);
	new->red_type = red_type;
	return (new);
}

void	*ft_free_redirect(t_redirect *to_free)
{
	free(to_free->file);
	return ((void *)to_free->file);
}
