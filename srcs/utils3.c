#include "../includes/minishell.h"

char	*cerca_variabile(char *line)
{
    char string[32767];
    int i;

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

enum e_type check_tokens_valid(t_token *token)
{
    if (token->next)
        token = token->next;
    while (token)
    {
        if (token->e_type != TK_ID && !ft_is_command(token->e_type))
            if (token->e_type == TK_PIPE || token->e_type == TK_GREATER \
             || token->e_type == TK_LOWER || token->e_type == TK_DGREA || token->e_type == TK_DLOW)
                if (token->prec->e_type != TK_ID || token->next->e_type != TK_ID)
                    return (0);
        token = token->next;
    }
    return (1);
}
