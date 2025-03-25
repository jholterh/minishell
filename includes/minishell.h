#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

// find the path to executables
char	**get_paths(char **envp);
char	*find_path(char **paths, char *command);
char	**prepare_args(char **paths, char *command);

#endif