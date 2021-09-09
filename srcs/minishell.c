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
	ft_add_list(token, TK_ID, ft_strdup(tmp), apici);
	//printf("%s", tmp);
	free(tmp);
	return (i);
}

void	set_cmd(t_token *token)
{
	if (token->next)
		token = token->next;
	while (token != NULL)
	{
		if (token->e_type == TK_ID)
		{
			if (!ft_strncmp((const char*)token->val, "echo", 5) || !ft_strncmp((const char*)token->val, "EHO", 5))
				token->e_type = CM_ECHO;
			else if (!ft_strncmp((const char*)token->val, "cd", 3))
				token->e_type = CM_CD;
			else if (!ft_strncmp((const char*)token->val, "pwd", 4) || !ft_strncmp((const char*)token->val, "PWD", 4))
				token->e_type = CM_PWD;
			else if (!ft_strncmp((const char*)token->val, "export", 7))
				token->e_type = CM_EXP;
			else if (!ft_strncmp((const char*)token->val, "unset", 6))
				token->e_type = CM_UNS;
			else if (!ft_strncmp((const char*)token->val, "env", 4) || !ft_strncmp((const char*)token->val, "ENV", 4))
				token->e_type = CM_ENV;
			else if (!ft_strncmp((const char*)token->val, "exit", 5))
				token->e_type = CM_EXIT;
		}
		token = token->next;
	}
}

void	write_b(int n)
{
	while (n > 0)
	{
		printf("\b");
		n--;
	}
	return ;
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
			//printf(":%c", line[i]);
			if (is_token(line + i))
			{
				//printf("&%c&", line[i]);
				store_token(token, line + i);
				if (is_token(line + i) == 2)
					i++;
				continue;
			}
			else if (tmp)
			{
				// printf("&%s&\n", tmp);
				printf("%s", ft_strdup(tmp));
				write_b(ft_strlen(tmp));
				ft_add_list(token, TK_ID, ft_strdup(tmp), 0);
				ft_memset((void*)tmp, '\0', 30);
				continue;
			}
		}
	}
	if (line[i] == '\0' && tmp && *tmp != (char)NULL && line[i] != 32)
		ft_add_list(token, TK_ID, tmp, 0);
		// printf("&%s&\n", tmp);
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
		if (!strncmp(read, "", 2))
			continue;
		add_history(read);
		if (init_parsing(read) == 1 && *read != '\0')
		{
			printf("Error Parsing\n");
			free(read);
			continue ;
		}
		ft_parse_split(read, global->token);
		set_cmd(global->token);
		if (ft_parsing(global) == 0)
			printf("Errore Parser\n");
		else if (ft_parsing(global) == -1)
			return (0);
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

	token = ft_token_new(TK_ID, NULL, 0, NULL);
	global.argc = argc;
	global.argv = argv;
	global.envp = envp;
	global.token = token;

	if (!loop(&global))
		return (0);
}
