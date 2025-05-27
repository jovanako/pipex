/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:34:36 by jkovacev          #+#    #+#             */
/*   Updated: 2025/05/24 19:30:20 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	    ft_strlen(char *str);
int	    ft_strncmp(char *s1, char *s2, int n);
char    *copy(char *dst, char *src, int start);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
int		has_c(char *s, char c);