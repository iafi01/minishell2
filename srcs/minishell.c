#include "../includes/minishell.h"

void    sign_handler(int sig)
{
 	char		*read;

 	read = ft_strjoin(ft_strjoin("\e[0;32m<\e\033[0;37m", getenv("USER")),
 	           "\033[0;31m>\e \033[0;37m ");
    if (sig == SIGINT)
    {
 		ft_putstr_fd("\033[2D\033[0K", 1);
 		write(1, "\n", 1);
 		write(1, read, ft_strlen(read));
 	}
 	if (sig == SIGQUIT)
	{
 		ft_putstr_fd("\033[2D\033[0K", 1);
 	}
}

int	is_token(char *c)
{
	if (*c+1 && (ft_strncmp(c, ">>", 2) || ft_strncmp(c, "<<", 2)))
		return (2);
	if (*c == '>' || *c == '<' || *c == '|')
		return (1);
	return (0);
}

t_token	*ft_token_new(t_type token, char *val)
{
	t_token	*lnew;

	lnew = (t_token *)malloc(sizeof(t_token));
	lnew->e_type = token;
	lnew->val = val;
	return (lnew);
}

t_token	*ft_find_end(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_add_list(t_token *list, t_type token, char *val)
{
	list = ft_find_end(list);
	list->next = ft_token_new(token, val);
	return ;
}

void	store_token(t_token *list, char *t)
{
	if (ft_strncmp(t, ">>", 2))
		ft_add_list(list, TK_DGREA, NULL);
	else if (ft_strncmp(t, "<<", 2))
		ft_add_list(list, TK_DLOW, NULL);
	else if (*t == '>')
		ft_add_list(list, TK_GREATER, NULL);
	else if (*t == '<')
		ft_add_list(list, TK_LOWER, NULL);
	else if (*t == '|')
		ft_add_list(list, TK_PIPE, NULL);
	else if (*t == '>')
		ft_add_list(list, TK_GREATER, NULL);
}

char	**ft_parse_split(char *line, t_token *token)
{
	int len;
	int i;
	char *tmp;
	char	s[2];

	s[1] = '\0';
	i = 0;
	tmp = calloc(sizeof(char), 10);
	len = ft_strlen(line);
	while (line[i])
	{
		s[0] = line[i];
		if (is_token(line + i) == 2)
			i += 1;
		tmp = ft_strjoin(tmp, s);
		i++;
	}
	printf("%s", tmp);
}

int	loop(t_global *global)
{
	char		*read;
	t_token		token;
	while (1)
	{
		//signal(SIGINT, sign_handler);
		//signal(SIGQUIT, sign_handler);
		read = ft_strjoin(ft_strjoin("\e[0;32m<\e\033[0;37m", getenv("USER")),
	           "\033[0;31m>\e \033[0;37m ");
		read = readline(read);
		if (read == NULL)
			return (0);
		add_history(read);
		if (init_parsing(read) == 1 && *read != NULL)
		{
			printf("Error Parsing\n");
			free(read);
			continue ;
		}
		global->line = ft_parse_split(read, &token);
		free(read);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	global.argc = argc;
	global.argv = argv;
	global.envp = envp;

	if (!loop(&global))
		return (0);
}
