/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:15:54 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/08 12:33:36 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	size_t		i;
	size_t		len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *) s1);
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr((char *)set, (int)s1[i]) != 0)
		i++;
	while ((len > 0) && ft_strrchr((char *)set, (int)s1[len]) != 0)
		len--;
	res = ft_substr(s1, i, (ft_strlen(s1) - i - ft_strlen(&s1[len])) + 1);
	return (res);
}
