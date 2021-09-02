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
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	**ft_parse_split(char *line, t_token *token)
{
	int len;
	int i;
	char *tmp;

	i = 0;
	len = ft_strlen(line);
	while (line[i])
	{

		i++;
	}
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
		printf("%s", read);
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
