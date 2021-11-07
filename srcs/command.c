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
			i[1]++;
			continue ;
		}
		res[i[0]] = g_glbl.envp[i[1]];
		i[0]++;
		i[1]++;
	}
}

int	ft_unset(t_global *global)
{
	int		i[2];
	char	*find;
	int		s;
	char	**res;

	find = global->token->next->next->val;
	i[0] = 0;
	i[1] = 0;
	s = ft_get_size(global->envp);
	res = (char **)ft_malloc(sizeof(char *) * s);
	ft_unset_aux(i, s, find, res);
	if (i[0] != i[1])
	{
		free(global->envp);
		global->envp = res;
	}
	else
		free(res);
	global->ret = 0;
	return (0);
}

int	ft_env(t_global *global, int fd)
{
	int	i;

	i = 0;
	while (global->envp[i])
	{
		write(fd, global->envp[i], ft_strlen(global->envp[i]));
		write(fd, "\n", 1);
		i++;
	}
	global->ret = 0;
	return (0);
}

int	echo_loop(t_token *token, int *flag, t_global *global, int fd)
{
	while (token && !is_token_type(token->e_type))
	{
		if (!ft_strncmp(token->val, "-n", 2)
			&& ft_strncmp(token->val, "-n-", 3))
		{
			*flag = 1;
			token = token->next;
			continue ;
		}
		if (!ft_strncmp(token->val, "$?", 3))
		{
			ft_putnbr_fd(global->ret, fd);
			write(fd, "\n", 1);
			global->ret = 0;
			return (0);
		}
		write(fd, token->val, ft_strlen(token->val));
		token = token->next;
		write(fd, " ", 1);
	}
	if (*flag == 0)
		write(fd, "\n", 1);
	global->ret = 0;
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

int	ft_cd(t_token *token)
{
	char	*tmp;
	int		index;

	index = 1;
	if (token->next == NULL)
	{
		index = chdir(getenv("HOME"));
		g_glbl.ret = 0;
		return (0);
	}
	tmp = token->next->val;
	if (tmp[0] == '-')
		index = chdir(getenv("OLDPWD"));
	if (tmp[0] == 126 && tmp[1] == 47)
		tmp = ft_strjoin(getenv("HOME"), ft_substr(tmp, 1, ft_strlen(tmp)));
	index = chdir(tmp);
	if (index < 0 && tmp[0] != '-'
		&& !(tmp == NULL || ft_str_sim(&tmp[0], "~")))
		printf("cd: %s: %s\n", strerror(errno), tmp);
	g_glbl.ret = 0;
	return (0);
}
