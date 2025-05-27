/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:12:21 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/27 21:48:33 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "str_manipulation.h"

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
}   t_cmd;

t_cmd  *parse_input_cmd(t_cmd **execve_cmd, char *cmd);
int     parse_envp(char *envp[], t_cmd **execve_cmd);
char	*ft_substr(char *s, int start, int len);
void	free_arr_of_strings(char **arr);
void	free_tcmd(t_cmd *execve_cmd);
int     free_tcmd_and_return(t_cmd *execve_cmd);
int free_tcmd_and_exit(t_cmd *execve_cmd);
int		free_perror_and_return(t_cmd *execve_cmd, char *s);