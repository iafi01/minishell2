/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:59:13 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/12 15:45:38 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//function that returns the pointer to the environment variable passed in the argument
char	*ft_get_env_var(char *var, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && var[j] && env[i][j] == var[j])
			j++;
		if (env[i][j] == '=' && !var[j])
		{
			tmp = ft_strdup(env[i] + j + 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

char	*expand_env_var(char *str, int *i, char *result)
{
	int		j;
	char	*tmp;

	j = i[1] + 1;
	if (str[i[1]] == '$')
	{
		i[1]++;
		while (str[i[1]] && str[*i] != ' '
			&& str[i[1]] != '\t' && str[i[1]] != '\n' && str[i[1]] != '$'
			&& str[i[1]] != 39 && str[i[1]] != 34)
			i[1]++;
		tmp = ft_substr(str, j, i[1] - j);
		if (tmp)
		{
			result = ft_strjoin(result, getenv(tmp));
			*i += ft_strlen(tmp) + 1;
			free(tmp);
		}
	}
	return (result);
}

void	dollar_expand(char *line, char **tmp, int *j)
{
	if (line[j[1]] == '$')
	{
		*tmp = expand_env_var(line, j, *tmp);
		j[1]--;
	}
}

void	str_unica_complement(char *s, char *line, char **tmp, int *j)
{
	char	*trash;

	s[0] = line[j[1]];
	trash = ft_strjoin(*tmp, s);
	free(*tmp);
	*tmp = trash;
}

void	str_append(char *line, int *j, char **tmp, char *s)
{
	if (line[j[1] + 1] && line[j[1] + 1] != ' ')
		*tmp = str_2loop(line, j, *tmp, s);
}
