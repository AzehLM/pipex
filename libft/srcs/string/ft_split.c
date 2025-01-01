/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:15:58 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/01 18:50:44 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **split, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
	return (NULL);
}

static size_t	ft_count_string(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	len;
	size_t	i;
	size_t	start;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_count_string(s, c) + 1));
	if (!split)
		return (NULL);
	len = 0;
	i = 0;
	while (s[len] && i < (ft_count_string(s, c)))
	{
		while (s[len] && s[len] == c)
			len++;
		start = len;
		while (s[len] && s[len] != c)
			len++;
		split[i] = ft_substr(s, start, (len - start));
		if (!split[i++])
			return (ft_free(split, i - 1));
	}
	split[i] = 0;
	return (split);
}
