#include "../includes/minishell.h"

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
	while (i < s)
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
	global->envp = res;
}

void	ft_env(t_global *global)
{
	int	i;

	i = 0;
	while (global->envp[i])
		printf("%s\n",global->envp[i++]); 
}

void	ft_pwd(void)
{
	char dir[1024];
	printf("%s\n", getcwd(dir, sizeof(dir)));
}

int ft_echo(t_global *global)
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
		write(1, "\n", 1);
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
		write(1, token->val, ft_strlen(token->val));
		token = token->next;
		write(1, " ", 1);
	}
	if (flag == 0)
			write(1, "\n", 1);
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

/*
void	ft_print_alfa_env(char **envp, int	s)
{
	int	i;

	i = 0;
	while (i < s)
}

void	ft_export(t_token *list, char **envp, int size)
{
	if (list->next == NULL || strncmp(list->next->val, "", 2))
		ft_print_alfa_env(envp, size);
	else if (list->next && list->next->e_type == TK_ID && list->next->val[0] != '=')
	{
		envp = ft_realloc_env(envp);
		envp[size - 1] = ft_strdup(list->next->val);
	}
}

*/

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

void	ft_export(t_global *global)
{
	char *s1;
	char *s2;
	t_envp *env;
	t_envp *test;
	char **envp;
	int i;
	int j;

	i = 0;
	j = 0;
	envp = global->envp;
	test = env;
	while (envp[i])
	{
		env = ft_env_new(envp[i++]);
		env = env->next;
	}
	global->env = env;
	while (test->next)
	{
		printf("%s", test->first);
		test = test->next;
	}

	/*while (env)
	{
		env = ft_env_new(envp[i]);
		s1 = env->first;
		while (env)
		{
			s2 = env->first;
			if (ft_strcmp(s1, s2) == 1)
				env->index++;
			if (!env->next)
				break;
			env = env->next;
			j++;
		}
		i++;
	}*/
}
