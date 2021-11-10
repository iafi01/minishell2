/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:15:05 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/10 00:57:12 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cerca_variabile(char *line)
{
	char	string[32767];
	int		i;

	i = 0;
	while (line[i])
	{
		string[i] = line[i];
		if (getenv(string))
			return (getenv(string));
		i++;
	}
	return (NULL);
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

int	ft_get_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	**ft_copy_env(char **envp)
{
	int		s;
	int		i;
	char	**res;

	s = ft_get_size(envp);
	i = 0;
	res = (char **)ft_malloc(sizeof(char *) * s);
	while (i < s)
	{
		res[i] = envp[i];
		i++;
	}
	return (res);
}

//function that frees a list of commands
void	ft_free_cmd(t_command *cmd)
{
	t_command	*tmp;

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
