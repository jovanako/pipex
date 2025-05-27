/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:32:40 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/27 19:05:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	while ((n > 0) && (*s1 || *s2))
	{
		if ((*s1 - *s2) != 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (1);
}

char  *copy(char *dst, char *src, int start)
{
    int i;

    i = 0;
    while (src[start])
    {
        dst[i] = src[start];
        i++;
        start++;
    }
    dst[i] = '\0';
    return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;
	int 	len;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *) malloc (len * sizeof(char) + 1);
	if (result)
	{
		j = 0;
		while (s1[j] != '\0')
		{
			result[i++] = s1[j++];
		}
		j = 0;
		while (s2[j] != '\0')
		{
			result[i++] = s2[j++];
		}
		result[i] = '\0';
		return (result);
	}
	return ((void *)0);
}

int		has_c(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}