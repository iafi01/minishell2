/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:47:18 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 21:47:20 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set(t_global *global)
{
	int		s;
	char	**env;
	int		i;

	i = 0;
	s = ft_get_size(global->envp) + 1;
	env = malloc(sizeof(char *) * s + 1);
	if (sostitute_set(global, 1))
		return ;
	while (i < s - 2)
	{
		env[i] = ft_strdup(global->envp[i]);
		i++;
	}
	env[i++] = ft_strdup(global->token->next->next->val);
	env[i] = ft_strdup(global->envp[i - 1]);
	global->envp = env;
}

void	export_loop(int *i, t_envp *env, int fdo, t_envp *test)
{
	while (i[0] < i[1])
	{
		while (env)
		{
			if (env->index == i[0])
			{
				write(fdo, env->first, ft_strlen(env->first));
				write(fdo, "=", 1);
				write(fdo, env->second, ft_strlen(env->second));
				write(fdo, "\n", 1);
				i[0]++;
			}	
			env = env->next;
		}
		env = test->next;
	}
	return ;
}

int	ft_export(t_global *global, int fdo)
{
	t_envp	*env;
	t_envp	*test;
	char	**envp;
	int		i[2];

	i[0] = 0;
	envp = global->envp;
	i[1] = ft_get_size(global->envp);
	test = ft_env_new("init");
	env = test;
	create_export(envp, test);
	set_index_export(global, env);
	if (global->token->next->next)
	{
		ft_set(global);
		global->ret = 0;
		return (0);
	}
	export_loop(i, env, fdo, test);
	global->ret = 0;
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

void	ft_exit(t_global *global)
{
	int		i;
	char	**arr;

	arr = list_to_arr(global->token->next);
	if (arr[0] && arr[1] && arr[2])
	{
		write(2, "exit\n bash: exit: too many arguments\n", 38);
		global->ret = 1;
	}
	else
	{
		i = 0;
		while (arr[1] && global->argv[1] && ft_isdigit(global->argv[1][i]))
			i++;
		exit_if(arr, global, i);
		if (arr[1] && arr[1] != NULL && global->ret != 2)
			i = ft_atoi(arr[1]);
		else
			i = global->ret;
		exit(i);
	}
}
