/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:35:44 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/04 14:45:12 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	size_t			count;
	unsigned int	nb;

	count = 0;
	nb = n;
	if (n < 0)
	{
		count++;
		nb = n * -1;
	}
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count + 1);
}

char	*ft_itoa(int n)
{
	unsigned long	nb;
	size_t			len;
	char			*res;

	len = ft_len(n);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	len--;
	nb = n;
	if (n < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	if (n == 0)
		res[0] = 48;
	while (nb > 0)
	{
		res[len] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (res);
}
