/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:12:12 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/26 14:51:32 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int perror_and_return(char *s, int n)
{
    perror(s);
    return (n);
}

static int fork_pipe_left(char *cmd, int input_fd, int fd[], char *envp[])
{
    pid_t   pid;
    t_cmd   *execve_cmd;

    //fprintf(stderr, "about to parse input cmd\n");
    execve_cmd = parse_input_cmd(&execve_cmd, cmd);
    //fprintf(stderr, "done parsing input cmd\n");
    if (!execve_cmd) //close fds?
        return (0);
    pid = fork();
    if (pid == -1)
        perror_and_return("Error: fork failed", 0);
    if (pid == 0)
    {
        printf("Child PID: %d\n", getpid());
        sleep(10);
        if (dup2(fd[1], 1) == -1)
            perror_and_return("Error: dup failed", 0);
        if (dup2(input_fd, 0) == -1)
            perror_and_return("Error: dup failed", 0);
        close(input_fd);
        close(fd[0]);
        close(fd[1]);
        if (!parse_envp(envp, &execve_cmd))
            return (0);
        execve(execve_cmd->cmd, execve_cmd->args, envp);
        perror_and_return("Error: execve failed", 0);
    }
    return (1);
}

static int fork_pipe_right(char *cmd, int output_fd, int fd[], char *envp[])
{
    pid_t   pid;
    t_cmd   *execve_cmd;

    execve_cmd = parse_input_cmd(&execve_cmd, cmd);
    if (!execve_cmd) //close fds?
        return (0);
    pid = fork();
    if (pid == -1)
        perror_and_return("Error: fork failed", 0);
    if (pid == 0)
    {
        printf("Child PID: %d\n", getpid());
        sleep(10);
        if (dup2(fd[0], 0) == -1)
            perror_and_return("Error: dup failed", 0);
        if (dup2(output_fd, 1) == -1)
            perror_and_return("Error: dup failed", 0);
        close(output_fd);
        close(fd[0]);
        close(fd[1]);
        if (!parse_envp(envp, &execve_cmd))
            return (0);
        execve(execve_cmd->cmd, execve_cmd->args, envp);
        perror_and_return("Error: execve failed", 0);
    }
    return (1);
}

int main(int argc, char *argv[], char *envp[])
{
    int     fd[2];
    int     input_fd;
    int     output_fd;

    if (argc != 5)
        perror_and_return("Error: Invalid number of arguments", 1);
    if (pipe(fd) == -1)
        perror_and_return("Error: pipe failed", 1);
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
        perror_and_return("Error: open failed", 1);
    fork_pipe_left(argv[2], input_fd, fd, envp);       
    output_fd = open(argv[4], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (output_fd == -1)
        perror_and_return("Error: open failed", 1);
    fork_pipe_right(argv[3], output_fd, fd, envp);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}
