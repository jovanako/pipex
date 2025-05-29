/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:12:12 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/29 11:24:37 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int perror_and_return(char *s)
{
    perror(s);
    return (1);
}

static int fork_pipe_left(char *cmd, int input_fd, int fd[], char *envp[])
{
    pid_t   pid;
    t_cmd   *execve_cmd;

    execve_cmd = parse_input_cmd(&execve_cmd, cmd);
    if (!execve_cmd)
        return (0);
    pid = fork();
    if (pid == -1)
		return (free_perror_and_return(execve_cmd, "Error: fork failed"));
    if (pid == 0)
    {
        if (dup2(fd[1], 1) == -1)
			return (free_perror_and_return(execve_cmd, "Error: dup failed"));
        if (dup2(input_fd, 0) == -1)
			return (free_perror_and_return(execve_cmd, "Error: dup failed"));
        close(input_fd);
        close(fd[0]);
        close(fd[1]);
        if (!parse_envp(envp, execve_cmd))
            free_tcmd_error_and_exit(execve_cmd);
        if (execve(execve_cmd->cmd, execve_cmd->args, envp) == -1)
			return (free_perror_and_return(execve_cmd, "Error: execve failed"));
    }
	free_tcmd(execve_cmd);
    return (1);
}

static int fork_pipe_right(char *cmd, int output_fd, int fd[], char *envp[])
{
    pid_t   pid;
    t_cmd   *execve_cmd;

    execve_cmd = parse_input_cmd(&execve_cmd, cmd);
    if (!execve_cmd)
        return (0);
    pid = fork();
    if (pid == -1)
		return (free_perror_and_return(execve_cmd, "Error: fork failed"));
    if (pid == 0)
    {
        if (dup2(fd[0], 0) == -1)
			return (free_perror_and_return(execve_cmd, "Error: dup failed"));
        if (dup2(output_fd, 1) == -1)
            return (free_perror_and_return(execve_cmd, "Error: dup failed"));
        close(output_fd);
        close(fd[0]);
        close(fd[1]);
        if (!parse_envp(envp, execve_cmd))
            free_tcmd_error_and_exit(execve_cmd);
        if (execve(execve_cmd->cmd, execve_cmd->args, envp) == -1)
			return (free_perror_and_return(execve_cmd, "Error: execve failed"));
    }
	free_tcmd(execve_cmd);
    return (1);
}

int main(int argc, char *argv[], char *envp[])
{
    int     fd[2];
    int     input_fd;
    int     output_fd;

    if (argc != 5)
        return (perror_and_return("Error: Invalid number of arguments"));
    if (pipe(fd) == -1)
        return (perror_and_return("Error: pipe failed"));
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
        return (perror_and_return("Error: open failed"));
    fork_pipe_left(argv[2], input_fd, fd, envp);       
    output_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (output_fd == -1)
        return (perror_and_return("Error: open failed"));
    fork_pipe_right(argv[3], output_fd, fd, envp);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}
