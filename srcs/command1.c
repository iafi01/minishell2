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

int	ft_export(t_global *global, int fd)
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
				printf("%s=%s\n", env->first, env->second);
				i++;
			}	
			env = env->next;
		}
		env = test->next;
	}
	return (0);
}

int ft_exit(t_global *global)
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
}
