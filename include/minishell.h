/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:20:48 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/26 22:41:55 by eeravci          ###   ########.fr       */
/*   Updated: 2025/06/25 23:59:08 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/wait.h>


# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"


// define constants
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT, // >
	TOKEN_REDIR_IN, // <
	TOKEN_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_UNKNOWN
}	t_token_type;

// define structs 
typedef struct s_builtin
{
	char	*input;
	char	**args;
	int argc;
	int status_exit;
}			t_builtin;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	t_token_type	type; // from enum 
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	int					type; // REDIRECT_OUT, REDIRECT_IN, REDIRECT_APPEND..
	char				*file; //out.txt
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**argv; // ["cat", "file.txt", NULL]
	t_redirect			*redirects; //linked list of redirection 
	int					status_exit;
	int	argc;
	struct s_command	*next;
}	t_command;

typedef struct s_msh
{
	t_env		*dict_env; // listed list of env
	char		*input; //raw input from readline()
	t_token		*tokens;
	t_command	*cmds;
	int			exit_status;
	int			last_exit_code;
}	t_msh;

// function prototypes

// env_util.c
t_env		*create_env_node(const char *key, const char *value);
void		add_env_node(t_env **head, const char *key, const char *value);
t_env		*init_env(char **envp);
void		free_env_list(t_env **head);
void		print_env_list(t_env *head);

// token.c
t_token	*token_stream(t_msh *msh);
int	handle_word(t_msh *msh, int *i, t_token **tokens);

// token_special.c
int			handle_pipe(char *input, int *i, t_token **tokens);
int			handle_redir_out(char *input, int *i, t_token **tokens);
int			handle_redir_in(char *input, int *i, t_token **tokens);
int			handle_special_tokens(char *input, int *i, t_token **tokens);

// token_util.c
t_token		*new_token(char *value, t_token_type type);
void		add_token(t_token **head, t_token *new);
void		print_tokens(t_token *tokens);
void		free_tokens(t_token **tokens);

// token_word.c
char *extract_single_quote(char *input, int *i);
char *extract_double_quote(char *input, int *i, t_msh *msh);
char *extract_plain_text(char *input, int *i);

// token_word_util.c
char	*extract_var_name(const char *str, int *i);
char *get_variable_value(char *var, t_msh *msh);
char *strjoin_and_free(char *s1, char *s2);
char *handle_dollar_braces(char *input, int *i);
char *extract_dollar_value(char *input, int *i, t_msh *msh);


// parser.c
t_command	*init_command(void);
void		add_command(t_command **cmds, t_command *new);
void		add_argument(t_command *cmd, char *value);
void		add_redirect(t_command *cmd, t_token **tokens);
t_command	*parser(t_token *tokens);

// parser_util.c
void		print_redirects(t_redirect *redir);
void		print_command_list(t_command *cmds);
void		free_redirects(t_redirect *redir);
void		free_command_list(t_command *cmds);

// syntax_checker.c
int			check_pipe_syntax(t_token *tokens);

/*     cmd_exe.c         */
int is_builtin(char *cmd);
int execute_builtins(t_command *cmd, t_msh *shell);
void execute(t_msh *msh);

/*      builtins         */
int ft_echo(t_command *cmd);
int ft_cd(t_command *cmd, t_msh *shell);
int	ft_pwd(t_command *cmd);
int	ft_export(t_command *cmd, t_env **env_list);
int	ft_env(t_command *cmd, t_env *env_list);
int ft_exit(t_command *cmd);
int ft_unset(t_command *cmd, t_env **env_list);


/*      env_util         */
t_env *create_env_node(const char *key, const char *value);
void add_env_node(t_env **head, const char *key, const char *value);
t_env *init_env(char **envp);
void free_env_list(t_env **head);
void print_env_list(t_env *head);

/*      env_util2         */
char		*get_env_value(t_env *env, char *key);
void set_env_value(t_env **head, const char *key, const char *value);
void remove_env_key(t_env **head, const char *key);

/*     export_utils      */
int	is_valid_identifier(const char *key);
void	print_export_error(const char *arg);
int env_list_size(t_env *env);
void	sort_env_array(t_env **array, int size);

/*      signals           */
void handle_sigquit(int sig);
void handle_sigint(int sig);
void setup_signals(void);

#endif