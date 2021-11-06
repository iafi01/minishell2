/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 00:34:17 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 00:34:18 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redirect_maggiore(t_redirect *red, int *fdo)
{
	int	fd_new;

	if (*fdo != STDOUT_FILENO)
		close (*fdo);
	if (red->red_type == TK_GREATER)
		fd_new = open(red->file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd_new = open(red->file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_new < 0)
	{
		ft_print_error("Errore in open\n");
		return (-1);
	}
	*fdo = fd_new;
	return (0);
}

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split((envp[i]) + 5, ':');
	path = find_path2(paths, cmd);
	if (paths == NULL)
	{
		write (2, "Path é nullo\n", 13);
		return (NULL);
	}
	free_arr(paths);
	return (path);
}

int	ft_redirect_minore(char *file, int *fdi)
{
	int	fd_new;

	if (*fdi != STDIN_FILENO)
		close (*fdi);
	fd_new = open(file, O_RDONLY);
	if (fd_new < 0)
	{
		perror(file);
		ft_print_error("Errore open file\n");
		return (-1);
	}
	*fdi = fd_new;
	return (0);
}

void	ft_redirect_dminore(char *word, int *fdi)
{
	char	*read;
	int		fd[2];
	int		ret;

	ret = pipe(fd);
	if (*fdi != STDIN_FILENO)
		close (*fdi);
	read = ft_malloc(sizeof(char) * 30);
	while (1)
	{
		read = ">";
		read = readline(read);
		if (!ft_strncmp(read, word, ft_strlen(word) + 1))
		{
			free(read);
			close(fd[1]);
			*fdi = fd[0];
			return ;
		}
		write(fd[1], read, ft_strlen(read));
		write(fd[1], "\n", 1);
		free(read);
		read = ft_malloc(sizeof(char) * 30);
		read = ft_memset((void *)read, '\0', 30);
	}
}

void	ft_redirect(t_command *coms, int *fdi, int *fdo)
{
	t_list	*temp;

	temp = coms->here_doc;
	while (temp)
	{
		ft_redirect_dminore((char *)temp->content, fdi);
		temp = temp->next;
	}
	temp = coms->in;
	while (temp)
	{
		ft_redirect_minore((char *)temp->content, fdi);
		temp = temp->next;
	}
	temp = coms->out;
	while (temp)
	{
		ft_redirect_maggiore((t_redirect *)temp->content, fdo);
		temp = temp->next;
	}
}
