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

	while (line[++j[1]])
	{
		j[0]++;
		if (line[j[1]] == 0 || line[j[1]] == ' ')
			return (tmp);
		else if (line[j[1]] == 39)
		{
			str = ft_stringa_unica(line + j[1], j, 1);
			tmp = ft_strjoin(tmp, str);
			j[1] += ft_strlen(str);
			return (tmp);
		}
		else if (line[j[1]] == 34)
		{
			str = ft_stringa_unica(line + j[1], j, 2);
			tmp = ft_strjoin(tmp, str);
			j[1] += ft_strlen(str);
			return (tmp);
		}
		s[0] = line[j[1]];
		tmp = ft_strjoin(tmp, s);
		return (tmp);
	}
}

void	loop_core(t_global *global, char *read)
{
	ft_lexer(read, global->token);
	global->simple_cmd = ft_command_new();
	global->simple_cmd = ft_cmd_init(global->simple_cmd);
	ft_state_0(global->token->next, global->simple_cmd);
	ft_exe_commands(global, global->simple_cmd);
	ft_free_list(global->token);
	free(read);
}

char	*pre_loop(void)
{
	char	*user;
	char	*read;

	wait(0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	read = ft_strjoin("<", getenv("USER"));
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
	t_token	*token;

	glbl.pid = 0;
	token = ft_token_new(TK_ID, NULL, 0, NULL);
	glbl.ret = 0;
	glbl.argc = argc;
	glbl.argv = argv;
	glbl.token = token;
	glbl.envp = ft_copy_env(envp);
	glbl.size = ft_get_size(envp);
	if (!loop(&glbl))
		return (0);
}
