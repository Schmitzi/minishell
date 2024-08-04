/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:03:10 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/05/29 16:03:11 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		write(STDERR_FILENO, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_handler2(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		write(STDERR_FILENO, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	backslash(int signum)
{
	if (signum == SIGQUIT)
	{
		g_sig = SIGQUIT;
		write(STDERR_FILENO, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_reset(t_mini *mini, int signum)
{
	if (signum == SIGINT)
	{
		mini->errno_code = 130;
		g_sig = 0;
	}
	else if (signum == SIGQUIT)
	{
		mini->errno_code = 131;
		g_sig = 0;
	}
}
