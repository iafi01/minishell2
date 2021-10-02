# include "../includes/minishell.h"

t_command	*ft_state_4(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_PIPE)
	{
		write(1, "Pipe\n", 5);
		return (NULL);//da creare nuovo comando
	}
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
	{
		return (ft_state_1(token->next, cmd));
	}
	else if (token->e_type == TK_ID)
	{
		return (ft_state_10(token->next, cmd));
	}
	else if (token->e_type == TK_LOWER)
	{
		return (ft_state_2(token->next, cmd));
	}
	else if (token->e_type == TK_DLOW)
	{
		return (ft_state_3(token->next, cmd));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_11(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
		return (ft_state_10(token->next, cmd));
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_12(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
		return (ft_state_10(token->next, cmd));
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_13(t_token *token, t_command *cmd)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
		return (ft_state_10(token->next, cmd));
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}
