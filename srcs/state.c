#include "../includes/minishell.h"

t_command	*ft_state_0(t_token *token)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		return (ft_state_10(token->next));
	}
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
	{
		return (ft_state_1(token->next));
	}
	else if (token->e_type == TK_LOWER)
	{
		return (ft_state_2(token->next));
	}
	else if (token->e_type == TK_DLOW)
	{
		return (ft_state_3(token->next));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_10(t_token *token)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		return (ft_state_10(token->next));
	}
	else if (token->e_type == TK_GREATER || token->e_type == TK_DGREA)
	{
		return (ft_state_11(token->next));
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

t_command	*ft_state_1(t_token *token)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		return (ft_state_4(token->next));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_2(t_token *token)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		return (ft_state_4(token->next));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}

t_command	*ft_state_3(t_token *token)
{
	if (token == NULL)
	{
		return (NULL);
	}
	if (token->e_type == TK_ID)
	{
		return (ft_state_4(token->next));
	}
	else
	{
		write(1, "Parsing Error\n", 14);
		return (NULL);
	}
}
