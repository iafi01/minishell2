/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:28:45 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/12 17:20:31 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_token *token)
{
	char	*tmp;
	int		index;
	char	cwd[1024];

	index = 1;
	if (!token->next)
		return (0);
	ft_set(&g_glbl, ft_strjoin("OLDPWD=", ft_get_env_var("PWD", g_glbl.envp)));
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
	getcwd(cwd, sizeof(cwd));
	ft_set(&g_glbl, ft_strjoin("PWD=", cwd));
	if (index < 0 && tmp[0] != '-'
		&& !(tmp == NULL || ft_str_sim(&tmp[0], "~")))
		printf("cd: %s: %s\n", strerror(errno), tmp);
	g_glbl.ret = 0;
	return (0);
}

void	exit_if(char **arr, t_global *global, int i)
{
	if (arr[1] && global->argv[1] && global->argv[1][i])
	{
		write(2, "exit\nbash: exit: ", 17);
		write(2, arr[1], ft_strlen(arr[1]));
		write(2, ": numeric argument required\n",
			ft_strlen(": numeric argument required\n"));
		global->ret = 2;
	}
	return ;
}
