#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h> //wait
#include <stdlib.h>   //exit

#include "pipe.h"
#include "parse.h"

int is_piped(Char_ptr command)
{
    for (size_t i = 0; command[i] != '\0'; i++)
    {
        if (command[i] == '|')
        {
            return 1;
        }
    }
    return 0;
}

int get_command_length(Char_ptr *args)
{
    size_t indx = 0;
    while (args[indx] != NULL)
    {
        indx++;
    }
    return indx;
}

Commands_info *get_piped_commands(Char_ptr command)
{
    Commands_info *commands = malloc(sizeof(Commands_info));
    Char_ptr *all_commands = split(command, "|");
    commands->commands = malloc(sizeof(Char_ptr *) * get_command_length(all_commands));
    int length = 0;

    for (int i = 0; all_commands[i] != NULL; i++)
    {
        commands->commands[length] = split(all_commands[i], " ");
        length++;
    }
    commands->length = length;
    return commands;
}

void perform_pipe(Char_ptr **commands, int count)
{
    if (count == 0)
    {
        return;
    }
    
    int pipe_fd[2], pid_2;
    pipe(pipe_fd);
    pid_2 = fork();
    if (pid_2 == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        perform_pipe(commands, count -1);
        execvp(commands[count -1][0], commands[count -1]);
        fprintf(stderr, "rsh: %s command not found\n", commands[count -1][0]);
        exit(-1);
    }
    else
    {
        wait(&pid_2);
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        execvp(commands[count][0], commands[count]);
        fprintf(stderr, "rsh: %s command not found\n", commands[count][0]);
        exit(-1);
    }
}

void handle_pipes(Char_ptr command)
{
    signal(SIGINT, NULL); // quit ignored
    int pid;

    Commands_info *commands = get_piped_commands(command);
    
    pid = fork();
    if (pid == 0)
    {
        perform_pipe(commands->commands, commands->length -1);
    }
    else
    {
        wait(&pid);
    }
}
