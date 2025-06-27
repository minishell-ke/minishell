/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:42 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/26 22:44:36 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
int	main(int argc, char **argv, char **envp)
{
    t_msh msh;
    
    if (argc > 1 && argv)
    exit(1);
    ft_bzero(&msh, sizeof(t_msh));
    msh.dict_env = init_env(envp);
    // print_env_list(msh.dict_env);
    while (true)
    {
        msh.input = readline("minishell> ");
        if (!msh.input)
            break;
        add_history(msh.input); // save input history
        // ft_printf("\n%s\n",msh.input);
        msh.tokens = token_stream(msh.input, msh.dict_env);
        // print_tokens(msh.tokens);
        msh.cmds = parser(msh.tokens);
        free_tokens(&msh.tokens);
        execute(&msh);
        // print_command_list(msh.cmds);

        msh.tokens = token_stream(&msh);
        // print_tokens(msh.tokens);
        msh.cmds = parser(msh.tokens);
        free_tokens(&msh.tokens);
        // execute(&msh);
        print_command_list(msh.cmds);
        free_command_list(msh.cmds);
        free(msh.input);
    }
    free_env_list(&msh.dict_env);
	return (0);
}
*/

int	main(int argc, char **argv, char **envp)
{
    t_msh msh;

    if (argc > 1 && argv)
        exit(1);
    ft_bzero(&msh, sizeof(t_msh));
    msh.dict_env = init_env(envp);
    
    
    setup_signals(); //signal setup
    while (true)
    {
        msh.input = readline("\033[0;31mminishell> \001\033[0m\002");
        if (!msh.input) // if return null print exit + this is not a signal!
        {
            write(1, "exit\n", 5);
            break;
        }

        add_history(msh.input);
        msh.tokens = token_stream(msh.input, msh.dict_env);
        msh.cmds = parser(msh.tokens);
        free_tokens(&msh.tokens);
        print_command_list(msh.cmds);
        execute(&msh);
        free_command_list(msh.cmds);
        free(msh.input);
    }
    free_env_list(&msh.dict_env);
    return (0);
}