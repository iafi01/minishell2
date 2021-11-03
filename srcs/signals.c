/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 00:46:23 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 00:46:25 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_child_process(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	is_child_process(int signum)
{
	if (!kill(glbl.pid, signum))
	{
		if (signum == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			glbl.ret = 131;
		}
		else if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			glbl.ret = 130;
		}
	}
	else
		exit_child_process(signum);
}

void	sig_handler(int signum)
{
	if ((signum == SIGINT || signum == SIGQUIT) && glbl.pid != 0)
		is_child_process(signum);
	else
	{
		if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 2);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (signum == SIGQUIT)
		{
			ft_putchar_fd('\r', 2);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
