#include "../includes/minishell.h"

void ft_set(t_global *global)
{
	int s;
	char **env;
	int i;

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

int	ft_export(t_global *global, int fdo)
{
	t_envp *env;
	t_envp *test;
	char **envp;
	int i;
	int max;

	i = 0;
	envp = global->envp;
	max = ft_get_size(global->envp);
	test = ft_env_new("init");
	env = test;
	create_export(envp, test);
	set_index_export(global, env);
	if (global->token->next->next)
	{
		ft_set(global);
		return (0);
	}
	while (i < max)
	{
		while (env)
		{
			if (env->index == i)
			{
				write(fdo, env->first, ft_strlen(env->first));
				write(fdo, "=", 1);
				write(fdo, env->second, ft_strlen(env->second));
				write(fdo, "\n", 1);
		//		printf("%s=%s\n", env->first, env->second);
				i++;
			}	
			env = env->next;
		}
		env = test->next;
	}
	return (0);
}

/*int ft_exit(t_global *global)
{
	int var;
	char **arr;
	
	arr = list_to_arr(global->token->next);
	var = 0;
	if (arr[2])
	{
		write(2, "Too many args\n", ft_strlen("Too many args\n"));
		return (1);
	}
	if (arr[1])
	{
		var = ft_atoi(arr[1]);
		if (!ft_isnum(arr[1]))
			exit(255);
		if (var < 0)
			var = 256 + var;
		while (var >= 256)
			var -= 256;
		exit(var);
	}
	if (arr[0])
		exit(errno);
	return (0);
}*/

/*static void	free_param(t_global *global)
{
	free_matrix(global->envp);
	free_matrix(global->export);
	free_matrix(global->argv);
	free_matrix(global->cmds);
	free(global);
}*/

void		ft_exit(t_global *global)
{
	int i;
	char **arr;

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
		if (arr[1] && global->argv[1] && global->argv[1][i])
		{
			write(2, "exit\nbash: exit: ", 17);
			write(2, arr[1], ft_strlen(arr[1]));
			write(2, ": numeric argument required\n", ft_strlen(": numeric argument required\n"));
			global->ret = 2;
		}
		if (arr[1] && arr[1] != NULL && global->ret != 2)
		{
			i = ft_atoi(arr[1]);
		}
		else
			i = global->ret;
		// i = (arr[1] && global->ret != 2)
		// 	? ft_atoi(arr[1]) : global->ret;
		//free_param(global);
		exit(i);
	}
}
