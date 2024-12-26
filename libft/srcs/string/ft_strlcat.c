/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:14:48 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/07 21:28:16 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_src;
	size_t	len_dst;

	if (!size)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	j = len_dst;
	i = 0;
	if (size <= len_dst)
		return (len_src + size);
	while (src && src[i] && (i + len_dst + 1) < size)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	if (size > 0)
		dst[j] = '\0';
	return (len_dst + len_src);
}
