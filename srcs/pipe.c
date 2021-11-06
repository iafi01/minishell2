/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 00:27:54 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 00:27:56 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	parent_pipe(int *fd2, int *fd, t_command *cmd, t_global *global)
{
	pipe(fd2);
	if (dup2(STDIN_FILENO, fd2[0]) == -1)
	{
		ft_print_error("Error11\n");
		free(cmd);
		exit (-1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_print_error("Error11\n");
		free(cmd);
		exit (-1);
	}
	close(fd[1]);
	close(fd[0]);
	ft_exe_commands(global, cmd->next);
	if (dup2(fd2[0], STDIN_FILENO) == -1)
	{
		ft_print_error("Error11\n");
		free(cmd);
		exit (-1);
	}
	close(fd2[1]);
}

static void	child_pipe(int *fd, t_command *cmd, t_global *global)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		ft_print_error("Error11\n");
		free(cmd);
		exit (-1);
	}
	close(fd[0]);
	close(fd[1]);
	ft_exe_one(global, cmd);
	free(cmd);
	if (global->last)
		ft_free_list(global->token);
	exit(0);
}

static int	init_pipe(t_command *primo, t_command *secondo, int *fd)
{
	if (!primo || !secondo)
		return (0);
	if (pipe(fd) == -1)
	{
		ft_print_error("Error pipe\n");
		return (1);
	}
	return (2);
}

int	ft_redirect_pipe(t_global *global, t_command *cmd)
{
	t_command	*primo;
	t_command	*secondo;
	int			fd[2];
	int			fd2[2];
	pid_t		id;

	primo = cmd;
	secondo = cmd->next;
	id = init_pipe(primo, secondo, fd);
	if (id != 2)
		return ((int)id);
	id = fork();
	if (id < 0)
	{
		ft_print_error("Error fork\n");
		return (1);
	}
	if (id == 0)
		child_pipe(fd, cmd, global);
	else
	{
		parent_pipe(fd2, fd, cmd, global);
		waitpid(id, NULL, 0);
	}
	return (0);
}
