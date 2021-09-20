#include "../includes/minishell.h"

int ft_redirect_maggiore(t_global *global, t_token *token)
{
    return (1);
}

t_token *ft_first_cmd(t_token *list)
{
    while (list->prec != NULL && !is_token_type(list->prec->e_type))
    {
        list = list->prec;
    }
    list = list->next;
    return (list);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(*arr);
		*arr = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

char	*
find_path2(char **paths, char *cmd)
{
	int		i;
	char	*folder;
	char	*path;

	i = 0;
	while (paths[i])
	{
		folder = ft_strjoin(paths[i], "/");
		path = ft_strjoin(folder, cmd);
		ft_str_delete(&folder);
        //write (2, path, ft_strlen(path));
		if (access(path, F_OK) == 0)
			return (path);
		ft_str_delete(&path);
		i++;
	}
	if (!paths[i])
	{
        printf("Command not found");
		return (NULL);
    }
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split((envp[i]) + 5, ':');
    int j = 0;
	path = find_path2(paths, cmd);
    //write (2, path, ft_strlen(path));
	if (paths == NULL)
    {
		write (2, "Path é nullo", 12);
        return (NULL);
    }
    free_arr(paths);
	return (path);
}

int ft_redirect_pipe(t_global *global, t_token *token)
{
    t_token *primo;
    t_token *secondo;
    int fd[2];

    primo = ft_first_cmd(token);
    secondo = token->next;
    //printf("%s %s\n", primo->val, secondo->val);
    if (!primo || !secondo)
        return (0);
    if (pipe(fd) == -1)
    {
        printf("Error pipe");
        return (1);
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
        {
            write(2, "Error11\n", 30);
            return (0);
        }
        close(fd[1]);
        char **str;

        str = (char **)malloc(sizeof(char *) * 5);
        str[0] = "ls";
        str[1] = "-l";
        if (execve(find_path(global->envp, "ls"), str, global->envp) == -1)
        {
            write(2, strerror(errno), 9);
            return (0);
        }
    }
    else
    {
        wait(0);
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            write(2, "Error21\n", 30);
            return (0);
        }
        close(fd[0]);
        char **str2;
        str2 = (char **)malloc(sizeof(char *) * 5);
        str2[0] = "wc";
        str2[1] = "-l";
        if (execve(find_path(global->envp, "wc"), str2, global->envp) == -1)
        {
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            return (0);
        }
    }
}

/*int ft_redirect_pipe(t_global *global, t_token *token)
{
    t_token *primo;
    t_token *secondo;
    int fd[2];

    primo = ft_first_cmd(token);
    secondo = token->next;
    printf("%s %s\n", primo->val, secondo->val);
    if (!primo || !secondo)
        return (0);
    if (pipe(fd) == -1)
    {
        printf("Error pipe");
        return (1);
    }
    int id = fork();
     if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("input");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("%d\n", y);
    }
}*/

int ft_redirect_minore(t_global *global, t_token *token)
{

    return (1);

    
}

int ft_redirect_dmaggiore(t_global *global, t_token *token)
{
    return (1);

}

int ft_redirect_dminore(t_global *global, t_token *token)
{

    return (1);
}
    
