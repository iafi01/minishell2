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

int    ft_unset(t_global *global)
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
	return (0);
}

int	ft_env(t_global *global, int fd)
{
	int	i;

	i = 0;
	while (global->envp[i])
	{
		write(fd ,global->envp[i], ft_strlen(global->envp[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (0);
}

int	ft_pwd(int fd)
{
	char dir[1024];

	write(fd, getcwd(dir, sizeof(dir)), ft_strlen(getcwd(dir, sizeof(dir))));
	write(fd, "\n", 1);
	return (0);
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

int	ft_cd(t_token *token)
{
	char	*tmp;
	int		index;

	index = 1;
	if (token->next == NULL)
	{
		index = chdir(getenv("HOME"));
		return (0);
	}
	tmp = token->next->val;
	if (tmp[0] == '-')
		index = chdir(getenv("OLDPWD"));
	if (tmp[0] == 126 && tmp[1] == 47)
			tmp = ft_strjoin(getenv("HOME"),ft_substr(tmp, 1,ft_strlen(tmp)));
			index = chdir(tmp);
	if(index < 0 && tmp[0] != '-' &&!(tmp == NULL || ft_str_sim(&tmp[0],"~")))
		printf("cd: %s: %s\n", strerror(errno), tmp);
	return (0);
}
