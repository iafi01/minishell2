/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:36:05 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/16 11:36:07 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	all_n(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 'n')
			return (false);
	return (true);
}

//function that frees a list of t_envp
void	free_envp(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->first);
		free(tmp->second);
		free(tmp);
	}
}