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
	return (tmp);
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

//function that prints the list
void	ft_print_lst(t_list *lst)
{
	while (lst)
	{
		ft_putstr(lst->content);
		lst = lst->next;
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

//function that prints a list of t_token *
void	ft_print_token(t_token *token)
{
	write(1, "\n>>", 3);
	while (token)
	{
		ft_putstr(token->val);
		token = token->next;
	}
	write(1, "<<\n", 3);
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
	// printf("%p\n", read);
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
