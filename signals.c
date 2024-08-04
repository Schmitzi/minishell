/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:28:51 by miturk            #+#    #+#             */
/*   Updated: 2024/07/30 17:30:09 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(t_mini *mini)
{
	if (mini->mode == INTER)
		(signal (SIGINT, sig_handler), signal (SIGQUIT, backslash));
	else if (mini->mode == CHILD)
		(signal (SIGINT, sig_handler2), signal (SIGQUIT, SIG_DFL));
	else if (mini->mode == NO_INTER)
		(signal (SIGINT, sig_handler2), signal (SIGQUIT, SIG_IGN));
	else if (mini->mode == IN_HEREDOC)
		(signal (SIGINT, sig_heredoc), signal (SIGQUIT, SIG_IGN));
	else
		(signal (SIGINT, SIG_DFL), signal (SIGQUIT, SIG_IGN));
}

void	block_sig(void)
{
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
}

void	ft_mode(t_mini *mini, t_mode mode)
{
	mini->mode = mode;
	sig_init(mini);
}

void	print_header(void)
{
	printf("\n███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░");
	printf("██╗███████╗██╗░░░░░██╗░░░░░\n");
	printf("████╗░████║██║████╗░██║██║██╔═══");
	printf("═╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n");
	printf("██╔████╔██║██║██╔██╗██║██║╚█████╗░");
	printf("███████║█████╗░░██║░░░░░██║░░░░░\n");
	printf("██║╚██╔╝██║██║██║╚████║██║░╚═══█");
	printf("█╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n");
	printf("██║░╚═╝░██║██║██║░╚███║██║██████╔╝");
	printf("██║░░██║███████╗███████╗███████╗\n");
	printf("╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚════");
	printf("═╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n\n");
	printf("	  a project by Michael Naysmith and Miha Turk\n\n");
}
