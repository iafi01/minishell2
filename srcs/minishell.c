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
		else if (line[j[1]] == 39)
		{
			str = ft_stringa_unica(line + j[1], j, 1);
			trash = ft_strjoin(tmp, str);
			free(tmp);
			tmp = trash;
			j[1] += ft_strlen(str);
			return (tmp);
		}
		else if (line[j[1]] == 34)
		{
			str = ft_stringa_unica(line + j[1], j, 2);
			trash = ft_strjoin(tmp, str);
			free(tmp);
			tmp = trash;
			j[1] += ft_strlen(str);
			return (tmp);
		}
		s[0] = line[j[1]];
		trash = ft_strjoin(tmp, s);
		free(tmp);
		tmp = trash;
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

//function that frees a list
void	ft_free_lst(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}


//function that frees a list of commands
void	ft_free_cmd(t_command *cmd)
{
	t_command *tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		ft_free_lst(tmp->out);
		ft_free_lst(tmp->in);
		ft_free_lst(tmp->here_doc);
		ft_free_lst(tmp->par);
		free(tmp);
	}
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
		ft_free_list(global->token->next);
		ft_free_cmd(global->simple_cmd);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;

	g_glbl.pid = 0;
	token = ft_token_new(TK_ID, NULL, 0, NULL);
	g_glbl.ret = 0;
	g_glbl.argc = argc;
	g_glbl.argv = argv;
	g_glbl.token = token;
	g_glbl.envp = ft_copy_env(envp);
	g_glbl.size = ft_get_size(envp);
	if (!loop(&g_glbl))
		return (0);
}
