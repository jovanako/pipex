/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:40:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/26 14:32:05 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int  cmd_len(char *arr[])
{
    int count;

    count = 0;
    while (arr[count])
    {
        count++;
    }
    return (count);
}

// static int  malloc_and_copy(char *dst, char *src)
// {
//     dst = (char *) malloc ((ft_strlen(src) + 1) * sizeof(char));
//     if (!dst)
//         return (0);
//     dst = copy(dst, src, 0);
//     return (1);
// }

static int  args_to_struct(t_cmd **execve_cmd, char *cmd)
{
    char    **cmd_split;
    int     cmd_wcount;
    int     i;
    int     j;

    cmd_split = ft_split(cmd, ' ');
    cmd_wcount = cmd_len(cmd_split);
    (*execve_cmd)->cmd = (char *) malloc ((ft_strlen(cmd_split[0]) + 1) * sizeof(char));
    if (!(*execve_cmd)->cmd)
        return (free_tcmd_and_return(*execve_cmd));
    (*execve_cmd)->cmd = copy((*execve_cmd)->cmd, cmd_split[0], 0);
    (*execve_cmd)->args = (char **) malloc (cmd_wcount * sizeof(char *));
    if (!(*execve_cmd)->args)
        return (free_tcmd_and_cmd_and_return(*execve_cmd));
    i = 0;
    j = 1;
    while (i < cmd_wcount && j < cmd_wcount)
    {
        // if (!malloc_and_copy((*execve_cmd)->args[i], cmd_split[j]))
        //     return (free_full_t_cmd_and_return(*execve_cmd));
        (*execve_cmd)->args[i] = cmd_split[j];
        i++;
        j++;
    }
    (*execve_cmd)->args[i] = NULL;
    return (1);
}

t_cmd  *parse_input_cmd(t_cmd **execve_cmd, char *cmd)
{
    *execve_cmd = (t_cmd *) malloc (sizeof (t_cmd));
    if (!(*execve_cmd))
        return (0);
    if (has_c(cmd, ' '))
    {
        //fprintf(stderr, "found spaces in cmd\n");
        if (!args_to_struct(&(*execve_cmd), cmd))
            return (0);
    }
    else
    {
        (*execve_cmd)->cmd = (char *) malloc ((ft_strlen(cmd) + 1) * sizeof(char));
        if (!((*execve_cmd)->cmd))
            return (0);
        (*execve_cmd)->cmd = copy((*execve_cmd)->cmd, cmd, 0);
        (*execve_cmd)->args = NULL;
    }
    return (*execve_cmd);
}