/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:56:13 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/03 22:56:22 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_list_if(char **tmp, char **val)
{
	char	*trash;

	*tmp = getenv("HOME");
	if (++(*val))
	{
		trash = ft_strjoin(*tmp, *val);
		free(*tmp);
		*tmp = trash;
	}
}

int	ft_add_list(t_token *list, t_type type, char *val, int apici)
{
	char	*tmp;

	tmp = ft_calloc(30, sizeof(char));
	list = ft_find_end(list);
	if (val != NULL && val[0] == '~')
	{
		add_list_if(&tmp, &val);
		list->next = ft_token_new(type, ft_strdup(tmp), apici, list);
		free(val);
	}
	else if (val != NULL && val[0] == '$' && !ft_strncmp(val, "$?", 2))
		list->next = ft_token_new(type, ft_strjoin(ft_itoa(g_glbl.ret),
					&val[2]), apici, list);
	else
		list->next = ft_token_new(type, val, apici, list);
	free(tmp);
	return (0);
}

void	end_echo(int *flag, int fd, t_global *global)
{
	if (*flag == 0)
		write(fd, "\n", 1);
	global->ret = 0;
}

//external function
void	str_append(char *line, int *j, char **tmp, char *s)
{
	if (line[j[1]] && line[j[1] + 1])
		*tmp = str_2loop(line, j, *tmp, s);
}

//external function
void	ft_cd_home(char ***tmp)
{
	char	*str;
	char	*trash;

	trash = ft_substr(**tmp, 1, ft_strlen(**tmp));
	str = ft_get_env_var("HOME", g_glbl.envp);
	free(**tmp);
	**tmp = ft_strjoin(str, trash);
	free(str);
	free(trash);
}
