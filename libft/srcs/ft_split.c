/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:54:46 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 02:54:47 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			i++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**ft_close(char **split, int j)
{
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	i = 0;
	j = 0;
	index = -1;
	if (!s)
		return (0);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((((s[i] == c || i == ft_strlen(s)) && index >= 0)))
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	return (ft_close(split, j));
}
/*

static size_t	count_words(char const *s, char c)
{
	int		count;
	int		is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	w_s(char const *s, int pos, char c)
{
	size_t	len;

	len = 0;
	while (s[pos])
	{
		if (s[pos] == c)
			return (len);
		len++;
		pos++;
	}
	return (len);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	if (!(tab = malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
		{
			if (k == 0)
				if (!(tab[j] = (char*)malloc(sizeof(char) * w_s(s, i, c) + 1)))
					return (NULL);
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if ((s[i] == c && s[i + 1] != c && k > 0) && (k = 0) == 0)
			j++;
	}
	tab[count_words(s, c)] = NULL;
	return (tab);
}
*/
