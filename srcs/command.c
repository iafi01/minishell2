#include "../includes/minishell.h"

/*int	ft_echo(char *line, t_list *list)
{
    int		i;
	int		flag;
	int		space;
	int		apice;
	int c = 0;

	space = 0;
	flag = 0;
    i = 0;
	apice = 0;
	if (check_apice(line) != 1)
		return (0);
    while (line[i])
	{	
		if (line[i] == '\\')
			if (line[++i])
				write(1, &line[i++], 1);
		if (line[i] == '\'')
			apice += -1;
		if (line[i] == '-' && line[i + 1] == 'n')
		{
			flag = 1;
			i += 2;
		}
		else if (line[i] == '~')
			printf("%s", ft_substr(ft_getenv(list, "HOME"), 5, 
				ft_strlen(ft_getenv(list, "HOME"))));
		else if (line[i] == '$' && apice % 2 == 0 && ft_isalnum(line[i + 1]))
		{
			c = ft_print_envvar(line + i + 1, list);
			if (!c)
				return (0);
			i += c;
		}
		else if (line[i] != '"' && line[i] != '\'' && space == 1)
			printf("%c", line[i]);
		if (line[i] == ' ')
			space = 1;
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}*/

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

void	ft_cd(t_token *token)
{
	char	*tmp;
	int		index;
	char	*line;

	line = token->val;
	debug_list(token);
	index = 1;
	tmp = token->val;
	printf("%s",tmp);
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

/*int ft_tree(t_global *global)
{
    if (!ft_strncmp(global->line[0], "echo", 4) || !ft_strncmp(global->line[0], "ECHO", 4))
        ft_echo(global);
    else if (!ft_strncmp(global->line[0], "env", 3) || !ft_strncmp(global->line[0], "ENV", 3))
        ft_env(global);
    else if (!ft_strncmp(global->line[0], "pwd", 3) || !ft_strncmp(global->line[0], "PWD", 3))
        ft_pwd();
    else if (!ft_strncmp(global->line[0], "exit", 4))
        return (0);
    else if (!ft_strncmp(global->line[0], "export", 6))
        ft_export(global);
    else if (!ft_strncmp(global->line[0], "unset", 5))
        unset(global);
    else if (!ft_strncmp(global->line[0], "cd", 2))
        ft_cd(global);
    else
        printf("Comando sconosciuto\n"); // execve da addare
    return (1);
}*/