/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:59:52 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/27 21:48:23 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr_of_strings(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
	{
        free(arr[i]);
		i++;		
	}
	free(arr);
}


void free_tcmd(t_cmd *execve_cmd)
{
	if (execve_cmd->args)
		free_arr_of_strings(execve_cmd->args);
    free(execve_cmd);
}

int free_tcmd_and_return(t_cmd *execve_cmd)
{
	free_tcmd(execve_cmd);
    return (0);
}

int free_tcmd_and_exit(t_cmd *execve_cmd)
{
	free_tcmd(execve_cmd);
    exit(1);
}

int	free_perror_and_return(t_cmd *execve_cmd, char *s)
{
	if (execve_cmd->args)
		free(execve_cmd->args);
    free(execve_cmd);
	perror(s);
    return (0);
}