#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*string;

	string = (char *)malloc(sizeof(char) * size + 1);
	if (string == NULL)
		return (NULL);
	ft_memset(string, '\0', size + 1);
	return (string);
}

int	ft_word_len(char const *s, char c, int index)
{
	int	i;

	i = 0;
	while (s[index] == c)
		index++;
	while (s[index] != c && s[index] != '\0')
	{
		i++;
		index++;
	}
	return (i);
}

int	ft_word_count(char const *s, char c, int index)
{
	int	i;

	i = 0;
	if (!(s[index]))
		return (0);
	while (s[index] == c)
		index++;
	while (s[index] != '\0' && s[index] != c)
	{
		index++;
		i = 1;
	}
	return (i + ft_word_count(s, c, index));
}

char	**ft_populatearray(int count, char c, char const *s, char **array)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	j = 0;
	while (j < count)
	{
		k = 0;
		array[j] = ft_strnew(ft_word_len(s, c, i));
		if (!(array[j]))
			return (NULL);
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			array[j][k++] = s[i++];
		array[j++][k] = '\0';
	}
	array[j] = 0;
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		count;

	//if (s == NULL || c == (char) NULL)
	//	return (NULL);
	count = ft_word_count(s, c, 0);
	array = (char **)malloc(sizeof(char *) * count + 1);
	if (array == NULL)
		return (NULL);
	ft_populatearray(count, c, s, array);
	return (array);
}
