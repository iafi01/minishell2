#include "../includes/minishell.h"

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

void	debug_list(t_token *token)
{
	if (token->next)
		token = token->next;
	while (token != NULL)
	{
		printf("%s",token->val);
		token = token->next;
	}
}