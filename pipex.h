/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:12:21 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/24 22:00:24 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "str_manipulation.h"

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
}   t_cmd;

t_cmd  *parse_input_cmd(t_cmd **execve_cmd, char *cmd);
int     parse_envp(char *envp[], t_cmd **execve_cmd);
char	*ft_substr(char *s, int start, int len);
int     free_tcmd_and_return(t_cmd *execve_cmd);
int     free_tcmd_and_cmd_and_return(t_cmd *execve_cmd);
int     free_full_t_cmd_and_return(t_cmd *execve_cmd);
void    free_arr_of_strings(char *arr[]);