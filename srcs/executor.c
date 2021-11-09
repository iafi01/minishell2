/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:28:11 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 22:28:13 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exe_one(t_global *global, t_command *coms)
{
	int	fdi;
	int	fdo;
	int	ret;

	fdi = STDIN_FILENO;
	fdo = STDOUT_FILENO;
	ft_redirect(coms, &fdi, &fdo);
	ret = ft_exec_build_in(global, coms, fdi, fdo);
	return (ret);
}

void	ft_exe_commands(t_global *global, t_command *simple_coms)
{
	if (get_size_simple_com(simple_coms) > 1)
		ft_redirect_pipe(global, simple_coms);
	else
		ft_exe_one(global, simple_coms);
}

void	exec_child_proc(int *fds, t_command *cmd, t_global *global, char **arr)
{
	dup2(fds[0], 0);
	dup2(fds[1], 1);
	ft_lstadd_front(&cmd->par, ft_lstnew(cmd->cmd));
	arr = lst_to_arr(cmd->par);
	execve(find_path(global->envp, cmd->cmd), arr, global->envp);
	close(0);
	close(1);
	exit(0);
}

int	exec_ifs(t_command *cmd, t_global *global, int fdo)
{
	char	*trash;

	trash = str_tolower(cmd->cmd);
	if (!ft_strncmp(trash, "echo", 5) && ft_free(trash))
		return (ft_echo(global, fdo));
	else if (!ft_strncmp(trash, "env", 4) && ft_free(trash))
		return (ft_env(global, fdo));
	else if (!ft_strncmp(cmd->cmd, "cd", 3) && ft_free(trash))
		return (ft_cd(global->token->next));
	else if (!ft_strncmp(cmd->cmd, "export", 7) && ft_free(trash))
		return (ft_export(global, fdo));
	else if (!ft_strncmp(trash, "pwd", 4) && ft_free(trash))
		return (ft_pwd(fdo));
	else if (!ft_strncmp(cmd->cmd, "unset", 6) && ft_free(trash))
		return (ft_unset(global));
	else if (!ft_strncmp(cmd->cmd, "exit", 5) && ft_free(trash))
		ft_exit(global);
	free(trash);
	return (-1);
}

int	ft_exec_build_in(t_global *global, t_command *cmd, int fdi, int fdo)
{
	int		i;
	char	**arr;
	pid_t	pid;
	int		fds[2];

	arr = NULL;
	if (cmd->cmd == NULL)
		return (0);
	i = exec_ifs(cmd, global, fdo);
	if (i >= 0)
		;
	else
	{
		pid = fork();
		g_glbl.pid = pid;
		if (pid < 0)
			perror("error");
		fds[0] = fdi;
		fds[1] = fdo;
		if (pid == 0)
			exec_child_proc(fds, cmd, global, arr);
		else
			waitpid(pid, 0, 0);
	}
	return (i);
}
