#include "../includes/minishell.h"

t_token	*init_token(int type, char *val)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->val = val;
	return (token);
}

void debug(int d_apici, int s_apici, int prev_apici)
{
	printf("\n Debbug:\n");
	if (prev_apici == 1)
		printf("\t Primo apice singolo\n");
	if (prev_apici == 2)
		printf("\t Primo apice doppio\n");
	printf("\t Apice singolo: %d\n", s_apici);
	printf("\t Apice dpppio: %d\n", d_apici);
}

