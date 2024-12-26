/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:52:32 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/05 19:56:23 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	unsigned long	len_base;
	int				count;

	len_base = ft_strlen_secured(base);
	count = 0;
	if (nbr >= len_base)
	{
		count += ft_putnbr_base(nbr / len_base, base);
		count += ft_putchar(base[nbr % len_base]);
	}
	else
		count += ft_putchar(base[nbr % len_base]);
	return (count);
}

int	ft_puthexa_lowercase_flags(unsigned long n, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.hash == true && n != 0)
		count += ft_putstr("0x");
	count += ft_putnbr_base(n, "0123456789abcdef");
	return (count);
}

int	ft_puthexa_uppercase_flags(unsigned int n, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.hash == true && n != 0)
		count += ft_putstr("0X");
	count += ft_putnbr_base(n, "0123456789ABCDEF");
	return (count);
}

int	ft_ptrhexa(void *ptr)
{
	int				count;
	unsigned long	address;

	count = 0;
	if (!ptr)
		count += ft_putstr("(nil)");
	else
	{
		address = (unsigned long) ptr;
		count += ft_putstr("0x");
		count += ft_puthexa_lowercase(address);
	}
	return (count);
}

int	ft_unsigned_decimal(unsigned int n)
{
	unsigned long	ten_power;
	unsigned int	nb;
	int				count;

	ten_power = 1;
	nb = n;
	count = 0;
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
