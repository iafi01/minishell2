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

void	ft_set_fds(pid_t pid, int *fds, int fdi, int fdo)
{
	g_glbl.pid = pid;
	if (pid < 0)
		perror("error");
	fds[0] = fdi;
	fds[1] = fdo;
	return ;
}

t_bool	ft_str_unic_aux(int *j, char *line, int *ap)
{
	j[0]++;
	if (line[j[1]] == 39
		|| line[j[1]] == 34
		|| (line[j[1]] == '$' && ft_strncmp(line + j[1], "$?", 2) != 0))
	{
		if (line[j[1]] != '$' && ((*ap == 1 && line[j[1]] == 39)
				|| (*ap == 2 && line[j[1]] == 34)))
		{
			j[1]++;
			return (true);
		}
		if (line[j[1]] == 34)
			*ap = 2;
		else if (line[j[1]] == 39)
			*ap = 1;
	}
	return (false);
}

int	ft_lex_inception(char **tmp, char *line, t_token *token, int *i)
{
	if (**tmp == (char) NULL && line[*i] == 32)
		return (1);
	if (line[*i] && (is_token(line + *i) || line[*i] == 32))
		if (lex_last_if(line, i, token, tmp))
			return (1);
	return (0);
}
