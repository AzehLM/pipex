/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:38:02 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/10 23:52:53 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	uint8_t	*s2;
	uint8_t	c2;

	s2 = (uint8_t *) s;
	c2 = (uint8_t) c;
	i = 0;
	while (i < n)
	{
		if (c2 == s2[i])
			return ((uint8_t *) &s2[i]);
		i++;
	}
	return (NULL);
}
