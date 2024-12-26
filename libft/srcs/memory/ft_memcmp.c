/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:55:03 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/11 22:19:17 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	uint8_t	*str1;
	uint8_t	*str2;
	size_t	i;

	str1 = (uint8_t *) s1;
	str2 = (uint8_t *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1 && str2 && str1[i] == str2[i] && (i < n - 1))
		i++;
	return (str1[i] - str2[i]);
}
