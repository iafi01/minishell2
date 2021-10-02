#include "../includes/minishell.h"

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

void	set_index_export(t_global *global, t_envp *env)
{
	t_envp *s1 = env;
	t_envp *s2 = env;
	t_envp *res;
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
	global->env = env;
}

int sostitute_set(t_global *global, int export)
{
	int i;
	char *s;
	t_envp *env;
	int j;

	j = 0;
	env = global->env;
	if (export == 1)
		s = global->token->next->next->val;
	else
		s = global->token->next->val;
	i = 0;
	while (s[i])
	{
		if (s[i] == '=' || s[i] == '\0')
			break ;
		i++;
	}
	while (env)
	{	
		//printf("%s|%s|%s\n",env->first, s,global->envp[j]);
		if (!ft_strncmp(env->first, s, i))
		{
			env->first = env->first;
			global->envp[j-1] = s;
			return (1);
		}
		j++;
		env = env->next;
	}
	return (0);
}
