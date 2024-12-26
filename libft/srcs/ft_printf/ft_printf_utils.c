/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:51:52 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/05 19:57:36 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_secured(const char *s)
{
	int	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		count += ft_putstr("(null)");
	while (str && str[count])
	{
		write(1, &str[count], 1);
		count++;
	}
	return (count);
}

int	ft_putnbr_bonus(int n, t_flags flags, long ten_power, int count)
{
	long	nb;

	nb = n;
	if (n >= 0)
	{
		if (flags.sign)
			count += ft_putchar('+');
		else if (flags.space && !flags.sign)
			count += ft_putchar(' ');
	}
	if (nb < 0)
	{
		nb = nb * -1;
		count += ft_putchar('-');
	}
	while (nb / (ten_power * 10) != 0)
		ten_power *= 10;
	while (ten_power != 0)
	{
		count += ft_putchar((nb / ten_power) + 48);
		nb %= ten_power;
		ten_power /= 10;
	}
	return (count);
}

int	ft_puthexa_lowercase(unsigned long n)
{
	int	count;

	count = 0;
	count += ft_putnbr_base(n, "0123456789abcdef");
	return (count);
}
