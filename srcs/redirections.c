#include "../includes/minishell.h"

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

int ft_redirect_maggiore(t_global *global, t_token *token)
{
    int			fd;
	t_token		*temp;
	int			check;
	char		**strings;

	temp = token;
	while (1)
	{
		fd = open(temp->next->val, O_TRUNC | O_RDWR | O_CREAT, 0777);
		if (!temp->next->next || temp->next->next->e_type != 5)
			break;
		temp = temp->next->next;
		temp->e_type = 0;
	}
	if (fd == -1)
	{
		write (2, "Error in file opening\n", 23);
		return (-1);
	}
	strings = get_options(find_cmd(token));
	int i = 0;
	int pid = fork();
	if (pid == 0)
	{
		if ((dup2(fd, STDOUT_FILENO)) == -1)
		{
			close (fd);
			write (2, "Error in file redirection\n", 26);
			return (-1);
		}
		close (fd);
		if (execve(find_path(global->envp, strings[0]), strings, NULL) == -1)
        {
			perror(strerror(errno));
            exit (1);
        }
	}
	wait (0);
	close (fd);
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

char	*find_path2(char **paths, char *cmd)
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
		if (open(path, O_RDONLY) != -1)
			return (path);
		ft_str_delete(&path);
		i++;
	}
	if (open(cmd, O_RDONLY) != -1)
		return (cmd);
	if (!paths[i])
	{
        printf("Command not found\n");
		return (NULL);
    }
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
	path = find_path2(paths, cmd);
	if (paths == NULL)
    {
		write (2, "Path é nullo\n", 13);
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
    return (0);
}

int ft_redirect_minore(t_global *global, t_token *token)
{

    return (1);

    
}

int ft_redirect_dmaggiore(t_global *global, t_token *token)
{
    int			fd;
	t_token		*temp;
	int			check;
	char		**strings;

	temp = token;
	while (1)
	{
		fd = open(temp->next->val, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (!temp->next->next || temp->next->next->e_type != TK_DGREA)
			break;
		temp = temp->next->next;
		temp->e_type = 0;
	}
	if (fd == -1)
	{
		write (2, "Error in file opening\n", 23);
		return (-1);
	}
	strings = get_options(find_cmd(token));
	int i = 0;
	int pid = fork();
	if (pid == 0)
	{
		if ((dup2(fd, STDOUT_FILENO)) == -1)
		{
			close (fd);
			write (2, "Error in file redirection\n", 26);
			return (-1);
		}
		close (fd);
		if (execve(find_path(global->envp, strings[0]), strings, NULL) == -1)
        {
			perror(strerror(errno));
            exit (1);
        }
	}
	wait (0);
	close (fd);
	return (1);
}

int ft_redirect_dminore(t_global *global, t_token *token)
{

    return (1);
}