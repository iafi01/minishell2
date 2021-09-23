#include "../includes/minishell.h"

char	**get_options(t_token *token)
{
	char	**str;
	int		size;
	int		i;
	t_token *temp;

	i = 0;
	size = 1;
	if (!token)
		return (NULL);
	temp = token;
	if (token->next)
		temp = token->next;
	while(temp->e_type == CM_OPT && temp)
	{
		size++;
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	str = (char **)malloc(sizeof(char *) * size + 1);
	temp = token;
	while(i < size)
	{
		str[i] = ft_strdup(temp->val);
		temp = temp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

t_token *find_cmd(t_token *token)
{
	t_token *temp;

	temp = token;
	if (!temp || !temp->prec)
		return (NULL);
	temp = temp->prec;
	while (temp && temp->e_type != CM_CMD)
	{
		if (temp->e_type != CM_OPT)
			return (NULL);
		temp = temp->prec;
	}
	return (temp);
	
}

int		check_if_options(t_global *global, t_token *tkn, char *opt)
{
	if (!tkn->prec)
		return (0);
	if (opt && opt[0])
	{
		if (tkn->prec->e_type == CM_CMD)
			return(1);
		else if (tkn->prec->e_type == CM_OPT)
			return (1);
	}
	return (0);
}

int	check_if_cmd(t_token *tkn)
{
	static int i = 1;

	if (!tkn->prec)
		return (0);
	i++;
	if (tkn->prec->e_type == 5 || tkn->prec->e_type == 6)
		return (1);
	return(0);
}

char	*search_path(char **paths, char *cmd)
{
	int		i;
	char	*folder;
	char	*path;

	i = 0;
	if (open(cmd, O_RDONLY) != -1)
			return (cmd);
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
	if (!paths[i])
		return (NULL);
	if (open(path, O_RDONLY) != -1)
		return (cmd);
	return (NULL);
}

int	check_path(t_global *global, t_token *tkn, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (ft_strncmp(global->envp[i], "PATH=", 5))
		i++;
	paths = ft_split((global->envp[i]) + 5, ':');
	path = search_path(paths, cmd);
	if (!paths || !path)
        return (0);
	if (check_if_cmd(tkn) == 1)
	{
		free_arr(paths);
		free(path);
		path = NULL;
		return (0);
	}
    free_arr(paths);
	free(path);
	path = NULL;
	return (1);
}

int ft_listlen(t_token *token)
{
    int i;

    i = 0;
    while (token)
    {
        i++;
        token = token->next;
    }
    return (i);
}

char **list_to_arr(t_token *token)
{
    char **arg;
    int i;

    i = 0;
    arg = malloc(sizeof(char *) * ft_listlen(token));
    while (token)
    {
        arg[i++] = token->val;
        //printf ("%s\n", arg[i - 1]);
        token = token->next;
    }
    arg[i] = '\0';
    return (arg);
}

t_token *arr_to_list(char **arg)
{
    t_token *token;
    int i;

    i = 0;
    token = ft_token_new(TK_ID, NULL, 0, NULL);
    while (arg[i++])
        ft_add_list(token, TK_ID, arg[i], 0);
    return (token);
}

