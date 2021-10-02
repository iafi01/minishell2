#include "../includes/minishell.h"

// char	*search_path(char **paths, char *cmd)
// {
// 	int		i;
// 	char	*folder;
// 	char	*path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		folder = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(folder, cmd);
// 		ft_str_delete(&folder);
// 		if (open(path, O_RDONLY) != -1)
// 			return (path);
// 		ft_str_delete(&path);
// 		i++;
// 	}
// 	if (is_path(cmd))
// 		if (open(cmd, O_RDONLY) != -1)
// 			return (cmd);
// 	if (!paths[i])
// 		return (NULL);
// 	if (open(path, O_RDONLY) != -1)
// 		return (cmd);
// 	return (NULL);
// }

// int	check_path(t_global *global, t_token *tkn, char *cmd)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path;

// 	i = 0;
// 	while (ft_strncmp(global->envp[i], "PATH=", 5))
// 		i++;
// 	paths = ft_split((global->envp[i]) + 5, ':');
// 	path = search_path(paths, cmd);
// 	//printf ("Path found is: %s\n", path);
// 	if (!paths || !path)
//         return (0);
// 	if (check_if_cmd(tkn) == 1)
// 	{
// 		free_arr(paths);
// 		free(path);
// 		path = NULL;
// 		return (0);
// 	}
//     free_arr(paths);
// 	free(path);
// 	path = NULL;
// return (1);
// }

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
    arg[i] = 0;
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

