#include "minishell.h"

void ft_strfree(char **str)
{
    int i;

    if (str == NULL)
        return ;
    i = -1;
    while(str[++i] != NULL)
    {
        free(str[i]);
    }
    free(str);
}

char *find_path(char *command)
{
    char **path;
    char *env;
    char *final_path;
    char *tmp_path;
    int i;

    env = getenv("PATH");
    if (env == NULL)
    {
        printf("Env is not set\n");
        return(NULL);
    }
    path = ft_split(env, ':');
    if (path == NULL)
    {
        printf("split failed\n");
        return (NULL);
    }
    i = -1;
    while (path[++i])
    {
        tmp_path = ft_strjoin(path[i], "/");
        if (tmp_path == NULL)
        {
            printf("failed to add \"/\" to the path\n");
            ft_strfree(path);
            return (NULL);
        }
        final_path = ft_strjoin(tmp_path, command);
        if (final_path == NULL)
        {
            printf("failed to create final path\n");
            ft_strfree(path);
            return (NULL);
        }
        free(tmp_path);
        if (access(final_path, X_OK) == 0)
        {
            ft_strfree(path);
            return (final_path);
        }
        free(final_path);
    }
    ft_strfree(path);
    printf("command could not be found\n");
    return (NULL);
}

int redirect_fd(int fd, int to_replace_fd) {
    if (fd != to_replace_fd) {
        if (dup2(fd, to_replace_fd) == -1) {
            perror("dup2");
            return 1;
        }
        close(fd);
    }
    return 0;
}

void execute_command(t_parsed_command *commands, int num_commands) {
    int pipe_fds[2];
    int input_file_fd;
    int output_file_fd;
    int flags;
    pid_t pid;
    char *path_to_command;
    int i;

    i = -1;
    while (++i < num_commands)
    {
        if (i < num_commands - 1) {
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                return;
            }
            commands[i].pipe_out = pipe_fds[1];
            commands[i + 1].pipe_in = pipe_fds[0];
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return;
        }

        if (pid == 0) {
            if (commands[i].input_file)
            {
                input_file_fd = open(commands[i].input_file, O_RDONLY);
                if (input_file_fd == -1 || redirect_fd(input_file_fd, STDIN_FILENO) != 0)
                {
                    perror("input file");
                    exit(EXIT_FAILURE);
                }
            }

            if (commands[i].output_file)
            {
                flags = O_WRONLY | O_CREAT | (commands[i].append_mode ? O_APPEND : O_TRUNC);
                output_file_fd = open(commands[i].output_file, flags, 0644);
                if (output_file_fd == -1 || redirect_fd(output_file_fd, STDOUT_FILENO) != 0)
                {
                    perror("output file");
                    exit(EXIT_FAILURE);
                }
            }

            if (commands[i].pipe_in != -1)
            {
                redirect_fd(commands[i].pipe_in, STDIN_FILENO);
            }
            if (commands[i].pipe_out != -1)
            {
                redirect_fd(commands[i].pipe_out, STDOUT_FILENO);
            }

            path_to_command = find_path(commands[i].command);
            if (path_to_command == NULL || execve(path_to_command, commands[i].arguments, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }

        if (commands[i].pipe_in != -1) close(commands[i].pipe_in);
        if (commands[i].pipe_out != -1) close(commands[i].pipe_out);
    }

    i = -1;
    while (++i < num_commands)
    {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    t_parsed_command commands[5];

    // Initialize commands as described previously
    commands[0].command = "cat";
    commands[0].arguments = (char *[]){"cat", "input.txt", NULL};
    commands[0].input_file = "input.txt";
    commands[0].output_file = NULL;
    commands[0].append_mode = 0;
    commands[0].pipe_in = -1;
    commands[0].pipe_out = -1;

    commands[1].command = "grep";
    commands[1].arguments = (char *[]){"grep", "pattern", NULL};
    commands[1].input_file = NULL;
    commands[1].output_file = NULL;
    commands[1].append_mode = 0;
    commands[1].pipe_in = -1;
    commands[1].pipe_out = -1;

    commands[2].command = "sort";
    commands[2].arguments = (char *[]){"sort", NULL};
    commands[2].input_file = NULL;
    commands[2].output_file = NULL;
    commands[2].append_mode = 0;
    commands[2].pipe_in = -1;
    commands[2].pipe_out = -1;

    commands[3].command = "tee";
    commands[3].arguments = (char *[]){"tee", "output.txt", NULL};
    commands[3].input_file = NULL;
    commands[3].output_file = "output.txt";
    commands[3].append_mode = 0;
    commands[3].pipe_in = -1;
    commands[3].pipe_out = -1;

    commands[4].command = "wc";
    commands[4].arguments = (char *[]){"wc", "-l", NULL};
    commands[4].input_file = NULL;
    commands[4].output_file = NULL;
    commands[4].append_mode = 0;
    commands[4].pipe_in = -1;
    commands[4].pipe_out = -1;

    execute_command(commands, 5);


    // Execution logic would follow here, using the parsed information


    // while (1)
    // {
    //     input = readline("my_shell> ");
    //     if (input == NULL) {
    //         printf("\nexit\n");
    //         break;
    //     }

    //     if (*input)
    //     {
    //         add_history(input);
    //     }
    //     printf("you entered \"%s\" as input\n", input);
    //     free(input);
    // }
    // printf("%s\n", getenv("PATH"));
    return 0;
}
