/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:03:07 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 01:03:09 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_state_13(t_token *token, t_command *cmd)
{
	if (token != NULL && token->e_type == TK_ID)
	{
		ft_lstadd_back(&cmd->here_doc, ft_lstnew(ft_strdup(token->val)));
		return (ft_state_10(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_command_new(void)
{
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	return (cmd);
}

t_command	*ft_cmd_init(t_command *cmd)
{
	cmd->cmd = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->here_doc = NULL;
	cmd->next = NULL;
	cmd->par = NULL;
	return (cmd);
}
