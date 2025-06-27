/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:36:00 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/25 23:37:06 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Extracts a variable name like USER from a string like $USER.
*/
char	*extract_var_name(const char *str, int *i)
{
	int	start;

	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup(""));
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_strndup(&str[start], *i - start));
}

char	*get_variable_value(char *var, t_msh *msh)
{
	char	*val;

	val = get_env_value(msh->dict_env, var);
	free(var);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (NULL);
	}
	free(s1);
	free(s2);
	return (res);
}

char *handle_dollar_braces(char *input, int *i)
{
    int start;
    char *var;

    start = ++(*i);
    while (input[*i] && input[*i] != '}')
        (*i)++;
    if (input[*i] != '}')
    {
        ft_putstr_fd("minishell: syntax error: missing '}' in ${VAR}\n", 2);
        return (ft_strdup(""));
    }
    var = ft_strndup(&input[start], *i - start);
    (*i)++;
    return (var);
}

char *extract_dollar_value(char *input, int *i, t_msh *msh)
{
	char	*var;

	(*i)++;
    if (input[*i] == '{')  //${var}
        var = handle_dollar_braces(input, i);
    else if (input[*i] == '?') // $?
    {
        (*i)++;
        return (ft_itoa(msh->exit_status)); 
    }
    else if (input[*i] && ft_isdigit(input[*i])) // $2 $1
    {
        (*i)++;
        return (ft_strdup(""));
    }  
    else if (input[*i] && (ft_isalpha(input[*i]) || input[*i] == '_'))
        var = extract_var_name(input, i);
    else
	    return (ft_strdup("$"));
    return (get_variable_value(var, msh));
}
