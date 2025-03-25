#include "minishell.h"

int main(int argc, char *argv[])
{
    char *input;
    while (1)
    {
        input = readline("minishell> ");
        if (input == NULL)
        {
            printf("exit\n");
            break ;
        }
        add_history(input);
        printf("You entered %s as input\n", input);
        free(input);
    }
    return (0);
}
