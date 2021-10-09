#include "minishell.h"

t_command	*ft_command_new(void)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	return (cmd);
}

t_command	*ft_cmd_init(t_command *cmd)
{
	cmd->cmd = NULL;
	cmd->in = ft_token_new(TK_ID, NULL, 0, NULL);
	cmd->out = ft_token_new(TK_ID, NULL, 0, NULL);
	cmd->here_doc = ft_token_new(TK_ID, NULL, 0, NULL);
	cmd->next = NULL;
	cmd->par = NULL;
	return (cmd);
}