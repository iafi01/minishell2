#include "../includes/minishell.h"

char	*ft_apici_split(char *line)
{
	int i;
	int apici;
	char *tmp;
	char s[2];

	s[1] = '\0';
	apici = 0;
	i = -1;
	tmp = calloc(30, sizeof(char)); //cambiare 30
	if (line[i] == 39)
		apici = 1;
	else if (line[i] == 34)
		apici = 2;
	while (line[++i])
	{
		if (line[i] == 32 /*|| is_token(line[i]) > 0*/)
			break ;
		if (line[i] == 39 || line[i] == 34)
		{
			if (line[i+1])
				i++;
			else 
				break ;
		}
		s[0] = line[i];
		tmp = ft_strjoin(tmp, s);
	}
	i++;
	//ft_add_list(token, TK_ID, ft_strdup(tmp), apici);
	//printf("%s", tmp);
	//free(tmp);
	return (tmp);
}

// void	set_cmd(t_token *token, t_global *global)
// {
// 	if (token->next)
// 		token = token->next;
// 	while (token != NULL)
// 	{
// 		if (token->e_type == TK_ID)
// 		{
// 			if (!ft_strncmp((const char*)token->val, "echo", 5) || !ft_strncmp((const char*)token->val, "ECHO", 5))
// 				token->e_type = CM_ECHO;
// 			else if (!ft_strncmp((const char*)token->val, "cd", 3))
// 				token->e_type = CM_CD;
// 			else if (!ft_strncmp((const char*)token->val, "pwd", 4) || !ft_strncmp((const char*)token->val, "PWD", 4))
// 				token->e_type = CM_PWD;
// 			else if (!ft_strncmp((const char*)token->val, "export", 7))
// 				token->e_type = CM_EXP;
// 			else if (!ft_strncmp((const char*)token->val, "unset", 6))
// 				token->e_type = CM_UNS;
// 			else if (!ft_strncmp((const char*)token->val, "env", 4) || !ft_strncmp((const char*)token->val, "ENV", 4))
// 				token->e_type = CM_ENV;
// 			else if (!ft_strncmp((const char*)token->val, "exit", 5))
// 				token->e_type = CM_EXIT;
// 			else if (!ft_strncmp((const char*)token->val, "$?", 3))
// 				token->e_type = EXIT_STATUS;
// 			else if (check_path(global, token, token->val) > 0)
// 				token->e_type = CM_CMD;
// 			else if (check_if_options(global, token, token->val) > 0)
// 				token->e_type = CM_OPT;
// 		}
// 		token = token->next;
// 	}
// }

char *ft_stringa_unica(char *line, int *j, int ap)
{
	int i;
	char *tmp;
	char s[2];

	s[1] = '\0';
	tmp = calloc(30, sizeof(char));
	i = 0;
	while (line[++i])
	{
		j[0]++;
		if ((line[i] == 39 && ap == 1) || (line[i] == 34 && ap == 2))
		{
			break ;
		}
		s[0] = line[i];
		tmp = ft_strjoin(tmp, s);
	}
	if (line[i + 1] && line[i + 1] != ' ')
	{
		while (line[++i])
		{
			j[0]++;
			if (line[i] == 0 || line[i] == ' ' || (line[i] == 39 && ap == 1) || (line[i] == 34 && ap == 2))
				break ;
			s[0] = line[i];
			tmp = ft_strjoin(tmp, s);
		}
	}
	//printf("tmp%s\n",tmp);
	if (line[i] == 34)
		tmp = ft_strjoin(tmp, ft_stringa_unica(line + i, j, 2));
	else if (line[i] == 39)
		tmp = ft_strjoin(tmp, ft_stringa_unica(line + i, j, 1));
	return (tmp);
}

void	ft_lexer(char *line, t_token *token)
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
		{
			if (line[i] == 34)
				ft_add_list(token, TK_ID, ft_stringa_unica(line + i, &i, 2), 2);
			else if (line[i] == 39)
				ft_add_list(token, TK_ID, ft_stringa_unica(line + i, &i, 1), 1);
			continue ;
		}
		if (line[i] == 34 || line[i] == 39)
		{
			ft_strjoin(tmp, ft_apici_split(line + i));
			continue ;
		}
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
	int	f;

	while (1)
	{
		//signal(SIGINT, sig_handler);
		//signal(SIGQUIT, sig_handler);
		read = ft_strjoin(ft_strjoin("\e[0;32m<\e\033[0;37m", getenv("USER")),
	           "\033[0;31m>\e \033[0;37m ");
		read = readline(read);
		if (read == NULL)
		{
			printf("exit");
			exit(0);
		}
		if (!strncmp(read, "", 2))
			continue;
		add_history(read);
		f = init_parsing(read);
		if (f == 1 && *read != '\0')
		{
			printf("Error Parsing\n");
			free(read);
			continue ;
		}
		ft_lexer(read, global->token);
		debug_list(global->token);
		global->simple_cmd = ft_command_new();
		global->simple_cmd = ft_cmd_init(global->simple_cmd);
		ft_state_0(global->token->next, global->simple_cmd);
		ft_exe_commands(global, global->simple_cmd);
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
	global.token = token;
	global.envp = ft_copy_env(envp);
	global.size = ft_get_size(envp);

	if (!loop(&global))
		return (0);
}
