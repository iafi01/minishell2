/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:21:24 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 20:21:26 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset_aux(int *i, int s, char *find, char **res)
{
	while (i[0] < s && g_glbl.envp[i[1]])
	{
		if (!ft_strncmp(g_glbl.envp[i[1]], find, ft_strlen(find)))
		{
			free(g_glbl.envp[i[1]]);
			g_glbl.envp[i[1]] = NULL;
			i[1]++;
			continue ;
		}
		res[i[0]] = g_glbl.envp[i[1]];
		i[0]++;
		i[1]++;
	}
}

int	ft_unset(t_global *global, char *find)
{
	int		i[2];
	int		s;
	char	**res;

	i[0] = 0;
	i[1] = 0;
	s = ft_get_size(global->envp);
	res = (char **)ft_malloc(sizeof(char *) * s);
	ft_unset_aux(i, s, find, res);
	if (i[0] != i[1])
	{
		free(global->envp);
		res[s - 1] = NULL;
		global->envp = res;
	}
	else
		free(res);
	global->ret = 0;
	return (0);
}

t_bool	ft_echo_first_if(t_token **token, t_bool *first, int *flag)
{
	t_bool	ret;

	ret = false;
	while (!ft_strncmp((*token)->val, "-n", 2)
		&& *first && all_n((*token)->val + 2))
	{
		*flag = 1;
		*first = false;
		*token = (*token)->next;
		if (!ft_strncmp((*token)->val, "-n", 2))
			*first = true;
		ret = true;
	}
	return (ret);
}

int	echo_loop(t_token *token, int *flag, t_global *global, int fd)
{
	t_bool	first;

	first = true;
	while (token && !is_token_type(token->e_type))
	{
		if (ft_echo_first_if(&token, &first, flag))
			continue ;
		if (!ft_strncmp(token->val, "$?", 3))
		{
			first = false;
			ft_putnbr_fd(global->ret, fd);
			if (token->next && token->next->e_type == TK_ID)
				write(fd, " ", 1);
			token = token->next;
			continue ;
		}
		write(fd, token->val, ft_strlen(token->val));
		first = false;
		if (token->next && token->next->e_type == TK_ID)
			write(fd, " ", 1);
		token = token->next;
	}
	end_echo(flag, fd, global);
	return (0);
}

int	ft_echo(t_global *global, int fd)
{
	t_token	*token;
	int		flag;

	flag = 0;
	token = global->token;
	if (!token->next)
		return (0);
	token = token->next;
	if (token->next == NULL)
	{
		write(fd, "\n", 1);
		global->ret = 0;
		return (0);
	}
	else
		token = token->next;
	return (echo_loop(token, &flag, global, fd));
}
