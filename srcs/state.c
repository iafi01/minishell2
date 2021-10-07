#include "../includes/minishell.h"

t_command	*ft_state_0(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		cmd->cmd = token->val;
		return (ft_state_10(token->next, cmd));
	}
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
	{
		if (token->next != NULL)
			ft_add_list(cmd->out, TK_ID, token->next->val, 0);
		else
		{
			write(1, "Parsing Error\n", 14);
			return (NULL);
		}
		return (ft_state_1(token->next, cmd));
	}
	else if (token->e_type == TK_LOWER)
	{
		if (token->next != NULL)
			ft_add_list(cmd->in, TK_ID, token->next->val, 0);
		else
		{
			write(1, "Parsing Error\n", 14);
			return (NULL);
		}
		return (ft_state_2(token->next, cmd));
	}
	else if (token->e_type == TK_DLOW)
	{
		if (token->next != NULL)
			ft_add_list(cmd->in, TK_ID, token->next->val, 0);
		else
		{
			write(1, "Parsing Error\n", 14);
			return (NULL);
		}
		return (ft_state_3(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_10(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (cmd);
	}
	if (cmd->par == NULL)
		cmd->par = token;
	if (token->e_type == TK_ID)
	{
		if (cmd->par == NULL)
			cmd->par = token;
		return (ft_state_10(token->next, cmd));
	}
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
	{
		if (token->next != NULL)
			ft_add_list(cmd->out, TK_ID, token->next->val, 0);
		else
		{
			write(1, "Parsing Error\n", 14);
			return (NULL);
		}
		return (ft_state_11(token->next, cmd));
	}
	else if (token->e_type == TK_PIPE)
	{
		write(1, "Pipe\n", 5);
		return (NULL);//creare un nuovo comando
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_1(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (cmd);
	}
	if (token->e_type == TK_ID)
	{
		cmd->cmd = token->val;
		return (ft_state_4(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_2(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		cmd->cmd = token->val;
		return (ft_state_4(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_3(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		cmd->cmd = token->val;
		return (ft_state_4(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}
