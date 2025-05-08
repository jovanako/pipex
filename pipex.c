/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:12:12 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/08 20:03:37 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int perror_and_return(char *s, int n)
{
    perror(s);
    return (n);
}

int fork_child(char *cmd, int input_fd, int output_fd, char *envVec[], int to_close)
{
    pid_t   pid;
    char    *argVec[] = { NULL };

    pid = fork();
    if (pid == -1)
        perror_and_return("Error: Fork failed", 0);
    if (pid == 0)
    {
        if (dup2(output_fd, 1) == -1)
            perror_and_return("Error: dup failed", 0);
        if (dup2(input_fd, 0) == -1)
            perror_and_return("Error: dup failed", 0);
        close(input_fd);
        close(output_fd);
        close(to_close);
        execve(cmd, argVec, envVec);
        perror_and_return("Error: execve failed", 0);
    }
    return (1);
}

int main(int argc, char *argv[])
{
    int     fd[2];
    int     input_fd;
    int     output_fd;
    char    *envp[] = { NULL };

    if (argc != 5)
        perror_and_return("Error: Invalid number of arguments", 1);
    if (pipe(fd) == -1)
        perror_and_return("Error: Pipe failed", 1);
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
        perror_and_return("Error: Open failed", 1);
    fork_child(argv[2], input_fd, fd[1], envp, fd[0]);       
    output_fd = open(argv[4], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (output_fd == -1)
        perror_and_return("Error: Open failed", 1);
    fork_child(argv[3], fd[0], output_fd, envp, fd[1]);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}
