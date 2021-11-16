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

void	ft_cd_pre_aux(char *trash, char ***tmp, t_token *token, int *index)
{
	trash = ft_get_env_var("PWD", g_glbl.envp);
	**tmp = ft_strjoin("OLDPWD=", trash);
	ft_set(&g_glbl, **tmp);
	free(trash);
	free(**tmp);
	**tmp = NULL;
	*tmp = &(token->next->val);
	if (**tmp && (**tmp)[0] == '-')
	{
		trash = ft_get_env_var("OLDPWD", g_glbl.envp);
		*index = chdir(trash);
		free(trash);
	}
}

int	ft_cd_aux(char ***tmp, int index, char *cwd)
{
	char	*trash;
	char	*str;

	if (**tmp && ft_strlen(**tmp) > 1 && (**tmp)[0] == 126 && (**tmp)[1] == 47)
	{
		trash = ft_substr(**tmp, 1, ft_strlen(**tmp));
		str = ft_get_env_var("HOME", g_glbl.envp);
		free(**tmp);
		**tmp = ft_strjoin(str, trash);
		free(str);
		free(trash);
	}
	index = chdir(**tmp);
	if (index < 0)
		return (0);
	getcwd(cwd, sizeof(cwd));
	trash = ft_strjoin("PWD=", cwd);
	ft_set(&g_glbl, trash);
	free(trash);
	if (index < 0 && (**tmp)[0] != '-'
		&& !(**tmp == NULL || ft_str_sim(&(**tmp)[0], "~")))
		printf("cd: %s: %s\n", strerror(errno), **tmp);
	g_glbl.ret = 0;
	return (0);
}

int	ft_cd(t_token *token)
{
	char	**tmp;
	char	*trash;
	int		index;
	char	cwd[1024];

	index = 1;
	trash = "init";
	tmp = &trash;
	if (token->next == NULL)
	{
		trash = ft_get_env_var("HOME", g_glbl.envp);
		index = chdir(trash);
		free(trash);
		g_glbl.ret = 0;
		return (0);
	}
	ft_cd_pre_aux(trash, &tmp, token, &index);
	return (ft_cd_aux(&tmp, index, cwd));
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
