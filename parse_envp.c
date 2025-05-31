/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:41:42 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/31 18:38:51 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char  *find_cmd(t_cmd *execve_cmd, char **s)
{
    char    *cmd_path;
	char	*full_cmd;
    int     i;

	full_cmd = ft_strjoin("/", execve_cmd->cmd);
    i = 0;
    while (s[i])
    {
        cmd_path = ft_strjoin(s[i], full_cmd);
        if (!cmd_path)
		{
			free(full_cmd);
            return ((void *)0); 
		}
        if (access(cmd_path, F_OK) == 0)
		{
			free(full_cmd);
            return (cmd_path);
		}
		free(cmd_path);
        i++;
    }
	free(full_cmd);
    return ((void *)0);
}

static char	*get_path(char *envp[], char **path_str, t_cmd *execve_cmd)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4))
        {
    		*path_str = (char *) malloc ((ft_strlen(envp[i]) - 4) * sizeof(char));
			if (!path_str)
			{
				free_tcmd(execve_cmd);
				return (0);
			}
    		*path_str = copy(*path_str, envp[i], 5);
			return (*path_str);            
        }
        i++;
    }
	write (2, "Error\n", 6);
    return (0);
}

static int	is_script(char *s)
{
	if (s[0] == '.' && s[1] == '/' && ft_strlen(s) > 2)
		return (1);
	return (0);
}

static int	is_full_path(t_cmd *execve_cmd)
{
	if (execve_cmd->cmd[0] == '/')
	{
        if (access(execve_cmd->cmd, F_OK) == 0)
			return (1);
		// perror("No such file or directory");
		return (free_tcmd_and_return(execve_cmd));
	}
	return (0);
}

int     parse_envp(char *envp[], t_cmd *execve_cmd)
{
    char    *path_str;
    char    **split_path;

	if (is_script(execve_cmd->cmd))
		return (1);
	if (is_full_path(execve_cmd))
		return (1);
	path_str = get_path(envp, &path_str, execve_cmd);
	if (!path_str)
		return (free_tcmd_and_return(execve_cmd));
    split_path = ft_split(path_str, ':');
    execve_cmd->cmd = find_cmd(execve_cmd, split_path);
    if (!(execve_cmd->cmd))
    {
        free(path_str);
        free_arr_of_strings(split_path);
        return (0);
    }
    free(path_str);
    free(split_path);
    return (1);
}
