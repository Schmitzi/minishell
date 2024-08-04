/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:16:00 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:33:02 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_name_gen(t_mini *mini)
{
	int		i;
	int		fd;
	int		bytes_read;
	char	*str;

	i = 2;
	str = (char *)malloc(sizeof(char) * 6);
	if (!str)
		return (ft_exit(mini, strerror(errno), 1, 0), NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (ft_exit(mini, strerror(errno), 1, 0), free(str), NULL);
	bytes_read = read(fd, str, 5);
	if (bytes_read == -1)
		return (ft_exit(mini, strerror(errno), 1, 0), free(str), NULL);
	str[0] = '_';
	str[1] = 'h';
	str[5] = '\0';
	close(fd);
	while (i < 5)
	{
		str[i] = (char)((unsigned int)str[i] % 26 + 'a');
		++i;
	}
	return (str);
}

int	heredoc_count(t_mini *mini)
{
	int	i;
	int	heredoc;
	int	in_quotes;

	i = 0;
	heredoc = 0;
	in_quotes = 0;
	if (!mini->input)
		return (false);
	while (mini->input[i])
	{
		if (mini->input[i] == '\"')
			in_quotes = !in_quotes;
		else if (!in_quotes && mini->input[i] == '<'
			&& mini->input[i + 1] == '<')
			heredoc++;
		i++;
	}
	mini->hd_count = heredoc;
	return (true);
}

void	arg_shuffle(char **args)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (args[0] == NULL)
		return ;
	while (args[i] != NULL)
	{
		if (!(ft_strcmp(args[i], " ") || !ft_strcmp(args[i], "")) && args)
		{
			j = i;
			while (args[j] != NULL && args[j + 1] != NULL)
			{
				temp = args[j];
				args[j] = args[j + 1];
				args[j + 1] = temp;
				j++;
			}
			args[j] = NULL;
			i = 0;
		}
		else
			i++;
	}
}

void	close_fds(void)
{
	int	i;
	int	tmp_fd;

	i = 3;
	while (i < 1000)
	{
		tmp_fd = dup(i);
		if (tmp_fd != -1)
		{
			close(i);
			close(tmp_fd);
		}
		i++;
	}
}

int	heredoc_tool(t_mini *mini, int i)
{
	if (mini->hd_count > 1 && g_sig == 0)
	{
		mini->heredoc = false;
		free_doc(mini->heredocs);
		return (true);
	}
	if (mini->args[0] && g_sig == 0 && mini->cmds[mini->i + 1] == NULL)
	{
		if (exe_heredoc(mini, mini->heredocs[i]) == false)
			return (free_doc(mini->heredocs), false);
	}
	mini->heredoc = false;
	return (true);
}
