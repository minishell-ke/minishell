/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:23:30 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/26 22:43:03 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Allocates a new command
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirects = NULL;
	cmd->status_exit = 0;
	cmd->next = NULL;
	cmd->argc = 0;
	return (cmd);
}

// appends a command to the command list
void	add_command(t_command **cmds, t_command *new)
{
	t_command	*tmp;

	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// adds tokens to argv (t_command)
void	add_argument(t_command *cmd, char *value)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	i = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(value);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc = count;
}

// handles <, >, <<, >>
void	add_redirect(t_command *cmd, t_token **tokens)
{
	t_redirect	*redir;
	t_redirect	*tail;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return ;
	redir->type = (*tokens)->type;
	*tokens = (*tokens)-> next;
	redir->file = ft_strdup((*tokens)->value);
	redir->next = NULL;
	if (!cmd->redirects)
		cmd->redirects = redir;
	else
	{
		tail = cmd->redirects;
		while (tail->next)
			tail = tail->next;
		tail->next = redir;
	}
}

// Main function that iterates over tokens
t_command	*parser(t_token *tokens)
{
	t_command	*cmds;
	t_command	*current;

	if (!tokens)
		return (NULL);
	if (check_pipe_syntax(tokens))
		return (NULL);
	cmds = NULL;
	while (tokens)
	{
		current = init_command();
		add_command(&cmds, current);
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			if (tokens->type == TOKEN_WORD)
				add_argument(current, tokens->value);
			else if (tokens->type >= TOKEN_REDIR_OUT
				&& tokens->type <= TOKEN_HEREDOC)
				add_redirect(current, &tokens);
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}
