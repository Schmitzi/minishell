/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:25:06 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/03 10:49:20 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_mini *mini)
{
	ft_mode(mini, CHILD);
	if (g_sig == SIGINT || g_sig == SIGQUIT)
		sig_reset(mini, g_sig);
	child_fds(mini);
	if (mini->args[0] && arg_checker(mini) == true)
	{
		if (is_builtin(mini) == false && mini->heredoc == false)
		{
			free(mini->cwd);
			mini->cwd = NULL;
			if (ft_strncmp(mini->args[0], "./", 2) == 0 || \
				ft_strncmp(mini->args[0], "../", 3) == 0)
			{
				if (access(mini->args[0], X_OK || F_OK) == -1)
					ft_exit(mini, "No such file or directory", 127, 0);
				else if (execve(mini->args[0], mini->args, mini->env) == -1)
					ft_exit(mini, "command not found", 126, 0);
			}
			else
				if (execve(mini->path, mini->args, mini->env) == -1)
					ft_exit(mini, "command not found", 127, 0);
		}
	}
	exit(mini->errno_code);
}

int	parent_process(t_mini *mini)
{
	if (mini->heredoc == true)
	{
		ft_mode(mini, IN_HEREDOC);
		if (heredoc(mini) == false)
			return (free_doc(mini->heredocs), free_parent(mini), false);
	}
	else if (mini->args[0] != NULL && is_builtin(mini) == true)
	{
		if (alias(mini) == false)
			return (free_parent(mini), true);
	}
	parent_fds(mini);
	correct_env(mini);
	free_parent(mini);
	return (true);
}

pid_t	create_child(t_mini *mini)
{
	pid_t	pid;

	if (mini->heredoc == true)
		return (1);
	if (!mini->args[0])
		return (1);
	if (ft_strcmp(mini->args[0], "") == 0)
		return (ft_exit(mini, "command not found", 1, 0), 1);
	if (mini->args[0] && is_builtin(mini) == true)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	set_args(t_mini *mini)
{
	if (find_entries(mini) == false)
		return (false);
	if (tokenize(mini) == false)
		return (free_array(mini->args), false);
	(space_trim(mini->args), arg_shuffle(mini->args));
	if (pre_expand(mini) == false)
		return (false);
	if (start_redir(mini) == false)
		return (false);
	if (redir_dir(mini) == false)
		return (false);
	if (cmd_check(mini) == false)
		return (false);
	if (mini->args[0] == NULL && (mini->outfile != NULL \
		|| mini->heredoc == true || mini->infile != NULL))
		return (true);
	if (re_arg_check(mini) == true)
		re_arg(mini);
	if (trim(mini) == false)
		return (false);
	if (pathfinder(mini) == false)
		return (false);
	if (mini->args[0] == NULL && mini->redir == true)
		return (false);
	return (correct_env(mini), true);
}

int	pre_expand(t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strchr(mini->args[i], '$') != NULL && \
		should_expand(mini->args[i]) == true)
		{
			temp = ft_strdup(mini->args[i]);
			if (temp == NULL)
				return (false);
			if (i > 0 && ft_strcmp(mini->args[i - 1], "<<") != 0)
			{
				free(mini->args[i]);
				mini->args[i] = expand_string(mini, temp);
				if (mini->args[i] == NULL)
					mini->args[i] = "";
			}
			free(temp);
		}
		i++;
	}
	return (true);
}
