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
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->par = NULL;
}