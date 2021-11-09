/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:18:51 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/09 13:26:42 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_path(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

//function that frees a pointer in argument and returns true
int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

//function that frees a list
void	ft_free_lst(t_list *lst)
{
	t_list	*tmp;

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

char	*str_2if(char *line, int *j, char *tmp)
{
	char	*str;
	char	*trash;

	if (line[j[1]] == 39)
	{
		str = ft_stringa_unica(line + j[1], j, 1);
		trash = ft_strjoin(tmp, str);
		tmp = trash;
		j[1] += ft_strlen(str);
		free(str);
		return (tmp);
	}
	else if (line[j[1]] == 34)
	{
		str = ft_stringa_unica(line + j[1], j, 2);
		trash = ft_strjoin(tmp, str);
		tmp = trash;
		j[1] += ft_strlen(str);
		free(str);
		return (tmp);
	}
	return (tmp);
}
