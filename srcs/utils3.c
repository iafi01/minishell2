#include "../includes/minishell.h"

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

char **ft_copy_env(char **envp)
{
	int		s;
	int		i;
	char	**res;

	s = ft_get_size(envp);
	i = 0;
	res = (char **)malloc(sizeof(char*) * s);
	while (i < s)
	{
		res[i] = envp[i];
		i++;
	}
	return (res);
}