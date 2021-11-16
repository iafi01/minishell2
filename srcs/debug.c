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

int	ft_add_list(t_token *list, t_type type, char *val, int apici)
{
	// char	**dollar;
	// int		i;
	char	*tmp;

	tmp = ft_calloc(30, sizeof(char));
	list = ft_find_end(list);
	if (val != NULL && val[0] == '~')
	{
		add_list_if(&tmp, &val);
		list->next = ft_token_new(type, ft_strdup(tmp), apici, list);
		free(val);
	}
	// else if (val != NULL && val[0] == '$'
	// 	&& val[1] != '?' && val[1] && apici != 1)
	// {
	// 	printf("|%s|\n", val);
	// 	add_list_loop(&dollar, &i, val, &tmp);
	// 	tmp = val;
	// 	list->next = ft_token_new(type, ft_strdup(tmp), apici, list);
	// 	free(val);
	// 	free(*dollar);
	// 	free(dollar);
	// }
	else if (val != NULL && val[0] == '$' && !ft_strncmp(val, "$?", 2))
		list->next = ft_token_new(type, ft_strjoin(ft_itoa(g_glbl.ret), &val[2]),
			apici, list);
	else
		list->next = ft_token_new(type, val, apici, list);
	free(tmp);
	return (0);
}

void	add_list_loop(char ***dollar, int *i, char *val, char **tmp)
{
	char	*trash[2];
	int		k;

	*i = -1;
	k = count_words(val, '$');
	*dollar = ft_split(val, '$');
	while (++(*i) < k)
	{
		trash[1] = ft_alpha_give((*dollar)[*i]);
		if (getenv(trash[1]))
		{
			trash[0] = ft_strjoin(*tmp, getenv(trash[1]));
			free(*tmp);
			*tmp = trash[0];
			free(trash[1]);
			trash[1] = ft_symbols_give((*dollar)[*i]);
			if (trash[1] != NULL)
			{
				trash[0] = ft_strjoin(*tmp, trash[1]);
				free(trash[1]);
				free(*tmp);
				*tmp = trash[0];
			}
		}
	}
}
*/
/*
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
