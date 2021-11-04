/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:02:11 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 01:02:13 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*ft_state_3(t_token *token, t_command *cmd)
{
	if (token != NULL && token->e_type == TK_ID)
	{
		ft_lstadd_back(&cmd->here_doc, ft_lstnew(token->val));
		return (ft_state_4(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*state_4_aux(t_command *cmd, t_token *token)
{
	if (cmd->next == NULL)
	{
		cmd->next = ft_command_new();
		ft_cmd_init(cmd->next);
		if (ft_state_0(token->next, cmd->next) == NULL)
		{
			write(1, "Parsing Error\n", 14);
			return (NULL);
		}
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
	return (cmd);
}

t_command	*ft_state_4(t_token *token, t_command *cmd)
{
	if (token == NULL)
		return (cmd);
	if (token->e_type == TK_PIPE)
		return (state_4_aux(cmd, token));
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
		return (ft_state_1(token->next, cmd, token->e_type));
	else if (token->e_type == TK_ID)
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup(token->val);
		return (ft_state_10(token->next, cmd));
	}
	else if (token->e_type == TK_LOWER)
		return (ft_state_2(token->next, cmd));
	else if (token->e_type == TK_DLOW)
		return (ft_state_3(token->next, cmd));
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_11(t_token *token, t_command *cmd, t_type red_type)
{
	if (token != NULL && token->e_type == TK_ID)
	{
		ft_lstadd_back(&cmd->out,
			ft_lstnew(ft_new_redirect(token->val, red_type)));
		return (ft_state_10(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_12(t_token *token, t_command *cmd)
{
	if (token != NULL && token->e_type == TK_ID)
	{
		ft_lstadd_back(&cmd->in, ft_lstnew(ft_strdup(token->val)));
		return (ft_state_10(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}
