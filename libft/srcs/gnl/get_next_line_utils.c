/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:40:45 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/04 22:31:27 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup_secured(const char *str)
{
	char		*dup;
	size_t		len;
	size_t		i;

	len = ft_strlen_gnl(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_gnl(const char *s1, const char *s2)
{
	ssize_t	len_s1;
	char	*res;
	ssize_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_secured(s2));
	if (!s2)
		return (ft_strdup_secured(s1));
	len_s1 = (size_t) ft_strlen_gnl(s1);
	res = malloc(sizeof(char) * (len_s1 + ft_strlen_gnl(s2) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i = -1;
	while (s2[++i])
		res[len_s1 + i] = s2[i];
	res[len_s1 + i] = '\0';
	return (res);
}

char	*ft_substr_secured(char const *s, unsigned int start, size_t len)
{
	char		*res;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen_gnl(s);
	if (start >= s_len)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s && s[i] && s[i] != (char) c)
		i++;
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (NULL);
}
