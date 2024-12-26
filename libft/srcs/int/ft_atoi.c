/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:32:49 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/11 23:37:53 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	res = 0;
	sign = -1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign *= 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (res >= LLONG_MAX / 10
			&& (res > LLONG_MAX / 10 || res > LLONG_MAX % 10))
			return (sign);
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	if (sign == 0)
		return ((int) res * -1);
	return ((int)res);
}
