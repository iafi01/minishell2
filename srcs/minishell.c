/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:30:48 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 19:30:50 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_2loop(char *line, int *j, char *tmp, char *s)
{
	char	*str;
	char	*trash;

	while (line[++j[1]])
	{
		j[0]++;
		if (line[j[1]] == 0 || line[j[1]] == ' ')
			return (tmp);
		str = tmp;
		tmp = str_2if(line, j, tmp);
		if (tmp != str)
		{
			free(str);
			return (tmp);
		}
		s[0] = line[j[1]];
		trash = ft_strjoin(tmp, s);
		free(tmp);
		tmp = trash;
		return (tmp);
	}
	return (tmp);
}

void	loop_core(t_global *global, char *read)
{
	ft_free_list(global->token);
	g_glbl.token = ft_token_new(TK_ID, NULL, 0, NULL);
	ft_lexer(read, global->token);
	free(read);
	global->simple_cmd = ft_command_new();
	global->simple_cmd = ft_cmd_init(global->simple_cmd);
	ft_state_0(global->token->next, global->simple_cmd);
	ft_exe_commands(global, global->simple_cmd);
	ft_free_cmd(global->simple_cmd);
}

char	*pre_loop(void)
{
	char	*user;
	char	*read;
	char	*trash;

	wait(0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	trash = getenv("USER");
	read = ft_strjoin("<", trash);
	user = ft_strjoin(read, "> ");
	free(read);
	read = readline(user);
	free(user);
	if (read == NULL)
	{
		printf("exit");
		exit(0);
	}
	return (read);
}

int	loop(t_global *global)
{
	char	*read;
	int		f;

	while (1)
	{
		read = pre_loop();
		if (!strncmp(read, "", 2))
			continue ;
		add_history(read);
		f = init_parsing(read);
		if (f == 1 && *read != '\0')
		{
			printf("Error Parsing\n");
			free(read);
			continue ;
		}
		loop_core(global, read);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	g_glbl.pid = 0;
	g_glbl.ret = 0;
	g_glbl.argc = argc;
	g_glbl.argv = argv;
	g_glbl.token = ft_token_new(TK_ID, NULL, 0, NULL);
	g_glbl.envp = ft_copy_env(envp);
	g_glbl.size = ft_get_size(envp);
	if (!loop(&g_glbl))
		return (0);
}
