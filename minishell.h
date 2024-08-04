/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:32:34 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 18:19:15 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <complex.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <features.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <term.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include "libft/libft.h"

// COLOURS
# define GREEN    "\033[1;32m"
# define RESET   "\033[0m" // No Colour

// SIGNALS
extern volatile sig_atomic_t	g_sig;

typedef enum s_mode
{
	INTER,
	NO_INTER,
	CHILD,
	IN_HEREDOC,
	IGNORE
}	t_mode;

// STRUCT
typedef struct s_env
{
	char			*key;
	char			*value;
	int				set;
	int				equals;
	struct s_env	*next;
}	t_env;

typedef struct s_doc
{
	pid_t	pid;
	int		fd;
	char	buffer[1024];
	int		bytes;
	char	*delim;
	char	*line;
	char	*name;
}	t_doc;

typedef struct s_cmd
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		quotes;
	int		quote_type;
}	t_cmd;

typedef struct s_token
{
	int		i;
	int		j;
	int		start;
	char	**str;
	int		isq;
	int		idq;
	int		count;
}	t_token;

typedef struct s_sort
{
	int				i;
	int				j;
	int				in_quotes;
	int				to_expand;
	int				is_escaped;
	int				len;
	int				flag;
	char			*new_str;
	struct s_sort	*next;
}	t_sort;

typedef struct s_exp
{
	int			isq;
	int			idq;
	char		*res;
	char		*res_ptr;
	const char	*p;
	const char	*var_start;
	size_t		var_len;
	char		*var_name;
	char		*var_value;
	size_t		value_len;
}	t_exp;

typedef struct s_mini
{
	char			**path_entries;
	char			**temp_env;
	char			**args;
	char			**env;
	char			**cmds;
	char			*path;
	char			*cwd;
	char			*oldpwd;
	char			*input;
	char			*infile;
	char			*outfile;
	int				orig_stdout;
	int				orig_stdin;
	int				errno_code;
	int				hd_count;
	int				heredoc;
	int				status;
	int				count;
	int				redir;
	int				exit;
	int				**fd;
	int				i;
	int				qflag;
	int				index;
	int				hd_i;
	char			*curr_pid;
	pid_t			*pid;
	t_mode			mode;
	t_sort			sort;
	t_cmd			info;
	t_token			token;
	t_exp			exp;
	t_doc			**heredocs;
}	t_mini;

// alias.c
int			alias(t_mini *mini);
void		ft_getcwd(t_mini *mini);
int			ft_cd(t_mini *mini);
int			arg_checker(t_mini *mini);

// builtins.c
int			is_builtin(t_mini *mini);
void		ft_echo(t_mini *mini);
int			ft_builtin_exit(t_mini *mini);
int			echo_tool(t_mini *mini);

//cd_tools.c
int			cd_add_arg(t_mini *mini);
int			cd_tilda(t_mini *mini);
void		shlvl_check(t_mini *mini);
char		**bubble_sort(char **arr);

// cmd.c
int			info_init(t_mini *mini);
int			cmd_split(t_mini *mini);
void		handle_quotes(t_mini *mini);
void		handle_pipe(t_mini *mini);
int			cmd_mem(t_mini *mini);

//env_name.c
char		*append_char(char *str, char c);
int			should_expand(char *str);

//env_utils.c
void		ft_env(t_mini *mini);
char		*env_loop(t_mini *mini, char *arg);
char		*env_name(t_mini *mini, char *arg);

//env_utils2.c
char		*ft_getpid(void);
int			correct_env(t_mini *mini);
int			count_args(char **args);

// env.c
char		*ft_getenv(t_mini *mini, char *env);
int			edit_env(t_mini *mini, char *key, char *value);
int			add_env(t_mini *mini, char *args);
int			backup_env(t_mini *mini);
int			edit_tool(t_mini *mini, char *key, char *value, int i);

//error.c
void		ft_exit(t_mini *mini, char *str, int errno_code, int fd);
void		clear_garbage(t_mini *mini);
void		ft_unset(t_mini *mini);

//expand_util.c
int			init_sort(t_sort *args, char *arg);
void		quotes_expand(t_sort *args, char c);
void		process_dollar_sign(t_sort *args, char *arg);
void		quote_toggle(t_sort *args, char c);

//expand.c
void		process_char(t_sort *args, char *arg);
char		*remove_quotes(t_mini *mini, char *arg);
int			trim(t_mini *mini);
int			access_check(t_mini *mini, char *input);
int			pipe_exit(t_mini *mini, long long error);

//export.c
int			process_loop(t_mini *mini, char *arg);
int			process_arg(t_mini *mini, char *arg);
int			ft_export(t_mini *mini);
int			env_check(t_mini *mini, char *arg);
int			export_name(t_mini *mini, char *args);
void		export_unset(t_mini *mini);

//free.c
void		cleanup_mini(t_mini *mini);
void		free_array(char **array);
void		free_pipes(t_mini *mini);
void		free_doc(t_doc **doc);
void		free_parent(t_mini *mini);

//ft_cd.c
int			cd_tools(t_mini *mini);
int			cd_dot_dot(t_mini *mini, char *dir);
int			cd_dash(t_mini *mini);

//heredoc.c
int			heredoc(t_mini *mini);
int			grab_line(t_mini *mini, t_doc *doc);
int			exe_heredoc(t_mini *mini, t_doc *doc);
int			heredoc_init(t_mini *mini);

//heredoc_stack.c
int			stack_heredocs(t_mini *mini);
int			pre_run(t_mini *mini);
pid_t		heredoc_child(t_mini *mini);

//heredoc_util.c
char		*heredoc_name_gen(t_mini *mini);
int			heredoc_count(t_mini *mini);
void		arg_shuffle(char **args);
int			in_quote(char *s);
int			heredoc_tool(t_mini *mini, int i);

//init.c
int			mini_init(t_mini *mini);
int			init_pipes(t_mini *mini);
void		re_arg(t_mini *mini);
long long	ft_atoll(const char *str);

//input.c
int			input_check(t_mini *mini, char **cmds);
int			builtin_check(char *str);
char		*str_cleaner(char *str, int i);
char		*ft_strncpy(char *destination, const char *source, size_t num);

//libft_plus.c
int			ft_isspace(int c);

//main.c
void		print_header(void);
char		*input_builder(t_mini *mini);
void		close_fds(void);
int			reset_shlvl(t_mini *mini);
void		ft_freemain(t_mini *mini);

//parsing.c
int			find_entries(t_mini *mini);
int			find_path(t_mini *mini);
int			path_tool(t_mini *mini);

//path.c
int			path_setter(t_mini *mini);
int			no_path(t_mini *mini);
int			pathfinder(t_mini *mini);
int			skip_space(const char *s);

//pipeing.c
int			child_process(t_mini *mini);
int			parent_process(t_mini *mini);
pid_t		create_child(t_mini *mini);
int			set_args(t_mini *mini);
void		parent_fds(t_mini *mini);

//pipeing_utils.c
void		child_fds(t_mini *mini);
int			cmd_check(t_mini *mini);

//prompt.c
void		prompt(t_mini *mini);
int			take_input(t_mini *mini);
int			ft_calling(t_mini *mini);
void		arg_count(t_mini *mini);

//quotes.c
int			syntax_pipe(char *str);
int			syntax_redir(t_mini *mini, char **args);
int			syntax_heredoc(char **args);

//redir_utils.c
int			redir_append(t_mini *mini);
int			redir_out(t_mini *mini);
int			redir_in(t_mini *mini);
int			redir_count(t_mini *mini);
int			in_check(t_mini *mini, char *arg);

//redir_utils2.c
int			handle_heredoc(t_mini *mini, int *i);
int			handle_redir_out(t_mini *mini, int *i);
int			handle_redir_in(t_mini *mini, int *i);
int			redir_dir(t_mini *mini);

//redir.c
int			redir_util2(t_mini *mini, int i);
int			redir_util1(t_mini *mini, int i);
void		redir_loop(t_mini *mini);
int			find_outfile(t_mini *mini);
int			start_redir(t_mini *mini);

//sig_handler.c
void		sig_handler(int signum);
void		sig_handler2(int signum);
void		sig_heredoc(int signum);
void		backslash(int signum);
void		sig_reset(t_mini *mini, int signum);

//signals.c
void		sig_init(t_mini *mini);
void		block_sig(void);
void		ft_mode(t_mini *mini, t_mode mode);

//syntax.c
int			syntax_check(char *s);

//utils.c
char		*pre_trim(char *input, char delim);
char		*post_trim(char *input, char delim);
char		*last_occur(char *input, char delim);
int			check_num(t_mini *mini, char *str);
void		space_trim(char **args);

//utils2.c
int			arg_formula(char *str);

//token_utils.c
int			handle_special_chars(t_token *token, char *input);
void		handle_spaces(t_token *token, char *input);
void		finalize_token(t_token *token, char *input);

//token.c
int			tokenize(t_mini *mini);
int			token_init(t_mini *mini);
void		toggle_quotes(t_token *token, char c);
char		*allocate_token(char *input, int start, int end);
void		special_loop(t_token *token, char *input);

int			find_good_dir(t_mini *mini, char *str);
void		ft_free(char *str);
void		move_to_end_and_free(char **array, int i);
void		trim_junk_args(t_mini *mini);
int			white_check(char **str);
int			re_arg_check(t_mini *mini);

char		*expand_string(t_mini *mini, char *input);
int			pre_expand(t_mini *mini);
int			reg_expand(t_mini *mini);
int			dir_check(t_mini *mini, char *str);
int			decide_quote(t_mini *mini, int *idq, int *isq);
void		handle__dec_quotes(const char **p, char **res_ptr, \
			int *isq, int *idq);
int			exp_init(t_exp *exp, char *input);
int			print_errno(t_mini *mini);
int			should_expand(char *str);
void		copy_char(const char **p, char **res_ptr);
int			handle_variable_expansion(t_mini *mini);
void		handle_dec_quotes(const char **p, char **res_ptr, \
			int *isq, int *idq);
int			deciding(t_mini *mini);

#endif
