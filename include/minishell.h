#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
//so on

// define constants
#define MAX_INPUT 1024
#define MAX_ARGS 100
#define PATH_MAX 4096
// define structs 
typedef struct s_list
{
    char *input; // for commands (cd, echo, pwd)
    char *output; // our result after command executed

} t_list;

// function prototypes

int ft_pwd(t_list *commands);

#endif