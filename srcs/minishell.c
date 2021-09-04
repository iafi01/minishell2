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
	if (*(c+1) && (!ft_strncmp(c, ">>", 2) || !ft_strncmp(c, "<<", 2)))
		return (2);
	if (*c == '>' || *c == '<' || *c == '|')
		return (1);
	return (0);
}

t_token	*ft_token_new(t_type token, char *val, int apici)
{
	t_token	*lnew;

	lnew = (t_token *)malloc(sizeof(t_token));
	lnew->e_type = token;
	lnew->val = val;
	lnew->apici = apici;
	lnew->next = NULL;
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

void	debug_list(t_token *token)
{
	while (token->next != NULL)
	{
		//if (token->e_type != 0)
		printf("%d",token->e_type);
		//else
		//printf("%s\n", token->val);
		token = token->next;
	}
}

void	ft_free_list(t_token *list)
{
	t_token	*first;
	t_token	*next;

	if (!list || list->next == NULL)
		return ;
	first = list;
	list = list->next;
	while (list->next != NULL)
	{
		next = list->next;
		if (list->e_type == TK_ID)
			free(list->val);
		free(list);
		list = next;
	}
	list = first;
	list->next = NULL;
}

void	ft_add_list(t_token *list, t_type type, char *val, int apici)
{
	list = ft_find_end(list);
	list->next = ft_token_new(type, val, apici);
	return ;
}

void	store_token(t_token *list, char *t)
{
	if (!ft_strncmp(t, ">>", 2))
		ft_add_list(list, TK_DGREA, NULL, 0);
	else if (!ft_strncmp(t, "<<", 2))
		ft_add_list(list, TK_DLOW, NULL, 0);
	else if (*t == '>')
		ft_add_list(list, TK_GREATER, NULL, 0);
	else if (*t == '<')
		ft_add_list(list, TK_LOWER, NULL, 0);
	else if (*t == '|')
		ft_add_list(list, TK_PIPE, NULL, 0);
	else if (*t == '>')
		ft_add_list(list, TK_GREATER, NULL, 0);
	else if (*t == '=')
		ft_add_list(list, TK_EQ, NULL, 0);
}

int	ft_apici_split(char *line, t_token *token)
{
	int i;
	int apici;
	char *tmp;
	char s[2];

	s[1] = '\0';
	apici = 0;
	i = 0;
	tmp = calloc(30, sizeof(char)); //cambiare 30
	if (line[i] == 39)
		apici = 1;
	else if (line[i] == 34)
		apici = 2;
	while (line[i++])
	{
		if (line[i] == 39 && apici == 1)
			break ;
		else if (line[i] == 34 && apici == 2)
			break;
		s[0] = line[i];
		tmp = ft_strjoin(tmp, s);
	}
	i++;
	ft_add_list(token, TK_ID, tmp, apici);
	printf("%s", tmp);
	free(tmp);
	return (i);
}

void	ft_parse_split(char *line, t_token *token)
{
	int len;
	int i;
	char *tmp;
	char	s[2];

	s[1] = '\0';
	i = -1;
	tmp = malloc(sizeof(char) * 30); //cambiare 30
	len = ft_strlen(line);
	while (line[++i])
	{
		if (line[i] == 34 || line[i] == 39)
			i += ft_apici_split(line + i, token);
		if (is_token(line + i) == 0 && line[i] != 32)
		{
			s[0] = line[i];
			tmp = ft_strjoin(tmp, s);
			s[0] = '\0';
		}
		if (*tmp == (char)NULL && line[i] == 32)
			continue;
		if (line[i] && (is_token(line + i) || line[i] == 32))
		{
			if (is_token(line + i))
			{
				store_token(token, line + i);
				if (is_token(line + i) == 2)
					i++;
				continue;
			}
			else if (tmp)
			{
				ft_add_list(token, TK_ID, ft_strdup(tmp), 0);
				ft_memset((void*)tmp, '\0', 30);
				continue;
			}
		}
	}
	if (line[i] == '\0' && tmp && *tmp != (char)NULL && line[i] != 32)
		ft_add_list(token, TK_ID, tmp, 0);
}

int	loop(t_global *global)
{
	char		*read;
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
		if (init_parsing(read) == 1 && *read != '\0')
		{
			printf("Error Parsing\n");
			free(read);
			continue ;
		}
		ft_parse_split(read, global->token);
		debug_list(global->token);
		ft_free_list(global->token);
		free(read);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	global;
	t_token		*token;

	token = ft_token_new(TK_ID, NULL, 0);
	global.argc = argc;
	global.argv = argv;
	global.envp = envp;
	global.token = token;

	if (!loop(&global))
		return (0);
}
