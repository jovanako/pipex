/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:40:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/28 22:19:58 by jkovacev         ###   ########.fr       */
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

static int  args_to_struct(t_cmd **execve_cmd, char *cmd)
{
    char    **cmd_split;
    int     cmd_wcount;
    int     i;

    cmd_split = ft_split(cmd, ' ');
    cmd_wcount = cmd_len(cmd_split);
    (*execve_cmd)->cmd = cmd_split[0];
	(*execve_cmd)->args = (char **) malloc ((cmd_wcount + 2) * sizeof(char *));
	if (!(*execve_cmd)->args)
	{
		free_arr_of_strings(cmd_split);
        return (free_tcmd_and_return(*execve_cmd));
	}
    i = 0;
    while (i < cmd_wcount)
	{
        (*execve_cmd)->args[i] = cmd_split[i];
		i++;
	}
    (*execve_cmd)->args[i] = NULL;
	free(cmd_split);
    return (1);
}

t_cmd  *parse_input_cmd(t_cmd **execve_cmd, char *cmd)
{
    *execve_cmd = (t_cmd *) malloc (sizeof (t_cmd));
    if (!(*execve_cmd))
        return (0);
	if (!args_to_struct(&(*execve_cmd), cmd))
		return (0);
    return (*execve_cmd);
}
