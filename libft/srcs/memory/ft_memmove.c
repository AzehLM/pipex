/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:19:10 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/11 22:20:09 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	uint8_t	*dest2;
	uint8_t	*src2;

	if (!dest && !src)
		return (NULL);
	dest2 = (uint8_t *) dest;
	src2 = (uint8_t *) src;
	if (src > dest)
		ft_memcpy(dest2, src2, n);
	else
	{
		while (n--)
			dest2[n] = src2[n];
	}
	return (dest);
}
