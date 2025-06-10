/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:49:02 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/11 00:46:40 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pwd(t_list *commands)
{
    char cwd[PATH_MAX];
    
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        commands->output = ft_strdup(cwd);
        printf("%s\n", cwd);
        return 0;
    }
    else
    {
        commands->output = ft_strdup("Error occured!");
        perror("pwd failed");
        return 1;
    }
}
