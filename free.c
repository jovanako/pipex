/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:59:52 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/24 22:02:50 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_arr_of_strings(char *arr[])
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
}

int free_tcmd_and_return(t_cmd *execve_cmd)
{
    free(execve_cmd);
    return (0);
}

int free_tcmd_and_cmd_and_return(t_cmd *execve_cmd)
{
    free(execve_cmd->cmd);
    free(execve_cmd);
    return (0);
}

int free_full_t_cmd_and_return(t_cmd *execve_cmd)
{
    free_arr_of_strings(execve_cmd->args);
    free(execve_cmd->args);
    return (free_tcmd_and_cmd_and_return(execve_cmd));
}