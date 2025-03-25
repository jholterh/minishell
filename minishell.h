#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_parsed_command{
    char *command;         // The command to be executed (e.g., "ls", "echo").
    char **arguments;      // Array of arguments for the command (e.g., {"-l", "/home"}).
    char *input_file;      // File for input redirection (e.g., "input.txt").
    char *output_file;     // File for output redirection (e.g., "output.txt").
    int append_mode;       // Boolean flag for appending output (1 if ">>", 0 if ">").
    int pipe_in;           // File descriptor for input pipe (used if part of a pipeline).
    int pipe_out;          // File descriptor for output pipe (used if part of a pipeline).
} t_parsed_command;


char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);

#endif