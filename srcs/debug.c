/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:23:16 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 01:23:18 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
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
		printf("%d|%s\n",token->e_type, token->val);
		token = token->next;
	}
}

void	print_tokens(t_global *global)
{
	t_global *temp;

	temp = global;
	if (!temp->token)
		return ;
	while (temp->token)
	{
		printf ("___________________________\n");
		printf("| "); printf("%s\n", temp->token->val);
		printf("| "); printf("%d\n", temp->token->e_type);
		if (!temp->token->next)
			break;
		temp->token = temp->token->next;
	}
	printf ("___________________________\n");
}


Modificare comando exit
Ritorni delle built-in -> $?
I segnali devono funzionare con ctrl-c e ctrl\ concatenati
Export fix seg_fault e fix errore duplicazione variabile aggiunta
Token Priority Management
Runnable executable dei comandi bin e degli eseguibili default es: ./minishell
Management dei Pipe |
Management Redirection >
Management Redirection <
Management Redirection <<
Management Redirection >>
*/
