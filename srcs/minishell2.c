/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:58:28 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/10 02:44:32 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_stringa_unica(char *line, int *j, int ap)
{
	char	*tmp;
	char	s[2];

	s[1] = '\0';
	tmp = ft_calloc(30, sizeof(char));
	j[1] = !(!ap) - 1;
	while (line[++j[1]])
	{
		j[0]++;
		if ((line[j[1]] == 39 && (ap == 1 || ap == 0))
			|| (line[j[1]] == 34 && (ap == 2 || ap == 0)) || line[j[1]] == '$')
		{
			if (line[j[1]] != '$')
				j[1]++;
			break ;
		}
		if (line[j[1]] == ' ' || line[j[1]] == '\t' || line[j[1]] == '\0')
			return (tmp);
		str_unica_complement(s, line, &tmp, j);
	}
	dollar_expand(line, &tmp, j);
	if (line[j[1] + 1] && line[j[1] + 1] != ' ')
		tmp = str_2loop(line, j, tmp, s);
	return (tmp);
}

static int	lex_last_if(char *line, int *i, t_token *token, char **tmp)
{
	if (is_token(line + *i))
	{
		store_token(token, line + *i);
		if (is_token(line + *i) == 2)
			(*i)++;
		return (0);
	}
	else if (*tmp)
	{
		ft_add_list(token, TK_ID, ft_strdup(*tmp), 0);
		free(*tmp);
		*tmp = (char *)ft_calloc(30, sizeof(char));
		ft_memset((void *)(*tmp), '\0', 30);
		return (0);
	}
	return (1);
}

static int	lex_first_2if(char *line, int *i, t_token *token, char *tmp)
{
	char	*trash;

	if (line[*i])
	{
		if (line[*i] == 34)
			ft_add_list(token, TK_ID, ft_stringa_unica(line + *i, i, 2), 2);
		else if (line[*i] == 39)
			ft_add_list(token, TK_ID, ft_stringa_unica(line + *i, i, 1), 1);
		else if (line[*i])
		{
			ft_add_list(token, TK_ID, ft_stringa_unica(line + *i, i, 0), 0);
			(*i)--;
		}
		return (1);
	}
	if (line[*i] == 34 || line[*i] == 39)
	{
		trash = ft_strjoin(tmp, ft_apici_split(line + *i));
		free(tmp);
		tmp = trash;
		return (1);
	}
	return (0);
}

static void	lex_2nd_if(char *line, int *i, char *s, char **tmp)
{
	char	*trash;

	if (is_token(line + *i) == 0 && line[*i] != 32)
	{
		s[0] = line[*i];
		trash = ft_strjoin(*tmp, s);
		free(*tmp);
		*tmp = trash;
		s[0] = '\0';
	}
}

void	ft_lexer(char *line, t_token *token)
{
	int		len;
	int		i[2];
	char	*tmp;
	char	s[2];

	s[1] = '\0';
	i[0] = -1;
	tmp = (char *)ft_calloc(30, sizeof(char));
	len = ft_strlen(line);
	while (line[++i[0]])
	{
		if (lex_first_2if(line, i, token, tmp))
			continue ;
		lex_2nd_if(line, i, s, &tmp);
		if (*tmp == (char) NULL && line[*i] == 32)
			continue ;
		if (line[*i] && (is_token(line + *i) || line[*i] == 32))
			if (lex_last_if(line, i, token, &tmp))
				continue ;
	}
	if (line[*i] == '\0' && tmp && *tmp != (char) NULL && line[*i] != 32)
		ft_add_list(token, TK_ID, ft_strdup(tmp), 0);
	free(tmp);
}
