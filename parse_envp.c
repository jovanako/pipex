/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:41:42 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/24 22:06:39 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char  *find_cmd(char *cmd, char **s)
{
    char    *cmd_path;
    int     i;

    i = 0;
    while (s[i])
    {
        cmd_path = ft_strjoin(s[i], cmd);
        if (!cmd_path)
            return ((void *)0); 
        if (access(cmd_path, F_OK) == 0)
            return (cmd_path);
        i++;
    }
    return ((void *)0);
}
static int     find_path_var(char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            return (i);
        }
        i++;
    }
    return (-1);
}

int     parse_envp(char *envp[], t_cmd **execve_cmd)
{
    int     path_i;
    char    *path_str;
    char    **split_path;

    path_i = find_path_var(envp);
    if (path_i < 0)
        return (0);
    path_str = (char *) malloc ((ft_strlen(envp[path_i]) - 4) * sizeof(char));
    if (!path_str)
        return (free_full_t_cmd_and_return(*execve_cmd));
    path_str = copy(path_str, envp[path_i], 5);
    split_path = ft_split(path_str, ':');
    (*execve_cmd)->cmd = find_cmd((*execve_cmd)->cmd, split_path);
    if (!((*execve_cmd)->cmd))
    {
        free(path_str);
        free_arr_of_strings(split_path);
        return (0);
    }
    free(path_str);
    free_arr_of_strings(split_path);
    return (1);
}
