#include "../includes/minishell.h"

/*int	ft_listlen(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}*/

void    ft_unset(t_global *global)
{
	int	i;
	char *find;
    int		s;
	char	**res;
    int     j;

	find = global->token->next->next->val;
	i = 0;
    j = 0;
	s = ft_get_size(global->envp);
	res = (char **)malloc(sizeof(char*) * s);
	while (i < s && global->envp[j])
	{
        if (!ft_strncmp(global->envp[j], find, ft_strlen(find)))
        {
		    j++;
			continue ;
		}
        res[i] = global->envp[j];
		i++;
        j++;
	}
	if (i != j)
		global->envp = res;
}

void	ft_env(t_global *global, int fd)
{
	int	i;

	i = 0;
	while (global->envp[i])
	{
		write(fd ,global->envp[i], ft_strlen(global->envp[i++]));
		write(fd, "\n", 1);
		i++;
	}
}

void	ft_pwd(int fd)
{
	char dir[1024];

	write(fd, getcwd(dir, sizeof(dir)), ft_strlen(getcwd(dir, sizeof(dir))));
	write(fd, "\n", 1);
}

int ft_echo(t_global *global, int fd)
{
	t_token *token;
	int flag;

	flag = 0;
	token = global->token;
	if (!token->next)
		return (0);
	token = token->next;
	if (token->next == NULL)
	{
		write(fd, "\n", 1);
		return (0);
	}
	else
		token = token->next;
	while (token && !is_token_type(token->e_type))
	{
		if (!ft_strncmp(token->val, "-n", 2) && ft_strncmp(token->val, "-n-", 3))
		{
			flag = 1;
			token = token->next;
			continue;
		}
		write(fd, token->val, ft_strlen(token->val));
		token = token->next;
		write(fd, " ", 1);
	}
	if (flag == 0)
		write(fd, "\n", 1);
	return (0);
}

void	ft_cd(t_token *token)
{
	char	*tmp;
	int		index;

	index = 1;
	if (token->next == NULL)
	{
		index = chdir(getenv("HOME"));
		return ;
	}
	tmp = token->next->val;
	if (tmp[0] == '-')
		index = chdir(getenv("OLDPWD"));
	if (tmp[0] == 126 && tmp[1] == 47)
			tmp = ft_strjoin(getenv("HOME"),ft_substr(tmp, 1,ft_strlen(tmp)));
			index = chdir(tmp);
	if(index < 0 && tmp[0] != '-' &&!(tmp == NULL || ft_str_sim(&tmp[0],"~")))
		printf("cd: %s: %s\n", strerror(errno), tmp);
}

t_envp	*ft_env_new(char *envp)
{
	t_envp	*lnew;
	char **c_split;

	lnew = (t_envp *)malloc(sizeof(t_envp));
	c_split = ft_split(envp, '=');
	if (c_split[0])
		lnew->first = c_split[0];
	else
		lnew->first = NULL;
	if (c_split[1])
		lnew->second = c_split[1];
	else
		lnew->second = NULL;
	lnew->index = 0;
	lnew->next = NULL;
	return (lnew);
}

void create_export(char **envp, t_envp *test)
{
	int i;

	i = 0;
	while (envp[i])
	{
		test->next = ft_env_new(envp[i++]);
		test = test->next;
	}
}

void	set_index_export(t_envp *env)
{
	t_envp *s1 = env;
	t_envp *s2 = env;
	while (s1)
	{
		while (s2)
		{
			if (ft_strcmp(s1->first, s2->first) == 1)
				s1->index++;
			s2 = s2->next;
		}
		//printf("%s %d\n",s1->first, s1->index);
		s1 = s1->next;
		s2 = env;
	}
}

int sostitute_set(t_global *global)
{
	int i;
	char *s;
	t_envp *env;
	int j;

	j = 0;
	env = global->env;
	s = global->token->next->next->val;
	i = 0;//non sostituisce un bel cazzo di niente
	while (s[i])
	{
		if (s[i] == '=' || s[i] == '\0')
			break ;
		i++;
	}
	while (env)
	{
		if (!ft_strncmp(env->first, s + i, ft_strlen(s+i)))
		{
			printf("%s==%s",env->first, s+i);
			global->envp[j] = s;
			return (1);
		}
		j++;
		env = env->next;
	}
	return (0);
}

void ft_set(t_global *global)
{
	int s;
	char **env;
	int i;

	i = 0;
	s = ft_get_size(global->envp) + 1;
	env = malloc(sizeof(char *) * s + 1);
	if (sostitute_set(global))
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

void	ft_export(t_global *global, int fd)
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
	if (global->token->next->next)
	{
		ft_set(global);
		return ;
	}
	set_index_export(env);
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
}
