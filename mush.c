#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    while (1)
    {
        char input[2048];
        // malloc this line

        printf("enter a comand :");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "cd", 2 ) == 0)
        {
            char *directory = strtok(input, " ");
            directory = strtok(NULL, " ");
            if (chdir(directory) == -1)
            {
                perror("chdir failed");
            }
        }
        else if (strcmp(input, "exit") == 0)
        {
            exit(0);
        }

        else
        {

            pid_t pid = fork();
            if (pid == 0)
            { // i am the child
                char *args[129];
                char *token = strtok(input, " ");
                int i = 0;
                while (token != NULL)
                {
                    args[i] = token;
                    token = strtok(NULL, " ");
                    i++;
                }
                args[i] = NULL;
                execvp(args[0], args);
                printf("execvp not working \n");
                exit(1);
            }

            else if (pid > 0)
            {
                // i am the parent
                wait(NULL);
            }
            else
            {
                printf("fork failed ");
                exit(1);
            }
        }
    }
    return 0;
}
