/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:23:26 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/26 22:44:01 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_redirects(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			ft_printf("    Redirect: < \"%s\"\n", redir->file);
		else if (redir->type == TOKEN_REDIR_OUT)
			ft_printf("    Redirect: > \"%s\"\n", redir->file);
		else if (redir->type == TOKEN_APPEND)
			ft_printf("    Redirect: >> \"%s\"\n", redir->file);
		else if (redir->type == TOKEN_HEREDOC)
			ft_printf("    Redirect: << \"%s\"\n", redir->file);
		else
			ft_printf("    Redirect: ? \"%s\"\n", redir->file);
		redir = redir->next;
	}
}

void	print_command_list(t_command *cmds)
{
	int	i;
	int	cmd_num;

	if (!cmds)
	{
		ft_printf("null\n");
		return ;
	}
	cmd_num = 1;
	while (cmds)
	{
		ft_printf("=== Command %d ===\n", cmd_num++);
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
			{
				ft_printf("    argv[%d]: \"%s\"\n", i, cmds->argv[i]);
				i++;
			}
		}
		print_redirects(cmds->redirects);
		ft_printf("%d\n", cmds->argc);
		ft_printf("-----------------\n");
		cmds = cmds->next;
	}
}

void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_command_list(t_command *cmds)
{
	t_command	*tmp;
	int			i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
			{
				free(tmp->argv[i]);
				i++;
			}
			free(tmp->argv);
		}
		free_redirects(tmp->redirects);
		free(tmp);
	}
}
