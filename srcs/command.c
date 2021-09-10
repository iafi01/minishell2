#include "../includes/minishell.h"

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
	global = 0;
	return (0);
}

void	ft_cd(t_token *token)
{
	char	*tmp;
	int		index;
	char	*line;

	line = token->val;
	debug_list(token);
	index = 1;
	tmp = token->val;
	write(1, tmp, ft_strlen(tmp));
	if (tmp == NULL || ft_str_sim(tmp, "~"))
	{
		index = chdir(getenv("HOME"));
		return ;
	}
	if (tmp[0] == '$')
		tmp = ft_strjoin(cerca_variabile(tmp + 1), tmp + count_var(tmp));
	if (tmp[0] == '-')
		index = chdir(getenv("OLDPWD"));
	if (line[0] == 126 && line[1] == 47)
			tmp = ft_strjoin(getenv("HOME"),ft_substr(tmp, 1,ft_strlen(tmp)));
			index = chdir(tmp);
	if(index < 0 && tmp[0] != '-' &&!(line == NULL || ft_str_sim(&line[0],"~")))
		printf("cd: %s: %s\n", strerror(errno), line);
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