# include "../includes/minishell.h"

t_command	*ft_state_4(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (cmd);
	}
	if (token->e_type == TK_PIPE)
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
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
	{
		// if (token->next != NULL && token->next->e_type == TK_ID)
		// 	ft_add_list(cmd->out, TK_ID, token->next->val, 0);
		// else
		// {
		// 	write(1, "Parsing Error\n", 14);
		// 	return (NULL);
		// }
		return (ft_state_1(token->next, cmd, token->e_type));
	}
	else if (token->e_type == TK_ID)
	{
		// if (cmd->par == NULL)
		// 	cmd->par = token;
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup(token->val);
		return (ft_state_10(token->next, cmd));
	}
	else if (token->e_type == TK_LOWER)
	{
		// if (token->next != NULL)
		// 	ft_add_list(cmd->in, TK_ID, token->next->val, 0);
		// else
		// {
		// 	write(1, "Parsing Error\n", 14);
		// 	return (NULL);
		// }
		return (ft_state_2(token->next, cmd));
	}
	else if (token->e_type == TK_DLOW)
	{
		// if (token->next != NULL)
		// 	ft_add_list(cmd->here_doc, TK_ID, token->next->val, 0);
		// else
		// {
		// 	write(1, "Parsing Error\n", 14);
		// 	return (NULL);
		// }
		return (ft_state_3(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_11(t_token *token, t_command *cmd, t_type red_type)
{
	// if (token == NULL)
	// {
	// 	return (NULL);
	// }
	if (token != NULL && token->e_type == TK_ID)
	{
		ft_lstadd_back(&cmd->out, ft_lstnew(ft_new_redirect(token->val, red_type)));
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
	// if (token == NULL)
	// {
	// 	return (NULL);
	// }
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

t_command	*ft_state_13(t_token *token, t_command *cmd)
{
	// if (token == NULL)
	// {
	// 	return (NULL);
	// }
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
