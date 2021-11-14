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
	int		j[2];
	char	*tmp;

	j[0] = 0;
	j[1] = 0;
	if (str[j[1]] == 34 || str[j[1]] == 39)
	{
		j[0]++;
		j[1]++;
	}
	if (str[j[1]] == '$' && str[j[1] + 1] != '?')
	{
		j[0]++;
		j[1]++;
		while (str[j[1]] && str[*i] != ' '
			&& str[j[1]] != '\t' && str[j[1]] != '\n' && str[j[1]] != '$'
			&& str[j[1]] != 39 && str[j[1]] != 34)
			j[1]++;
		tmp = ft_substr(str, j[0], j[1] - j[0]);
		if (tmp)
		{
			// result = ft_strjoin(result, );
			free(result);
			result = ft_get_env_var(tmp, g_glbl.envp);
			i[0]--;
			if (!result)
			{
				result = ft_strdup("");
				j[0] -= ft_strlen(tmp) + 1;
			}
			// *i += ft_strlen(result) + 1;
			free(tmp);
		}
	}
	return (result);
}

void	dollar_expand(char *line, char **tmp, int *j, int ap)
{
	line++;
	if (*(*tmp + !(!ap)) == '$' || **tmp == '$')
	{
		*tmp = expand_env_var(*tmp, j, *tmp);
		j[1]--;
	}
}

void	str_unica_complement(char *s, char *line, char **tmp, int *j)
{
	char	*trash;

	if (line[j[1]] == 34 || line[j[1]] == 39)
		return ;
	s[0] = line[j[1]];
	trash = ft_strjoin(*tmp, s);
	free(*tmp);
	*tmp = trash;
}

void	str_append(char *line, int *j, char **tmp, char *s)
{
	if (line[j[1]] && line[j[1] + 1]
		// && (line[j[1]] == 34 || line[j[1]] == 39)
		)
		*tmp = str_2loop(line, j, *tmp, s);
}
