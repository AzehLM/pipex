/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:50:45 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/05 19:56:35 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != (char) c)
		i++;
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (NULL);
}

static int	ft_convert_args(int convert, t_flags flags, va_list args)
{
	int	len;

	len = 0;
	if (convert == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (convert == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (convert == 'p')
		len += ft_ptrhexa(va_arg(args, void *));
	else if (convert == 'u')
		len += ft_unsigned_decimal(va_arg(args, unsigned int));
	else if (convert == 'x')
		len += ft_puthexa_lowercase_flags(va_arg(args, unsigned int), flags);
	else if (convert == 'X')
		len += ft_puthexa_uppercase_flags(va_arg(args, unsigned int), flags);
	else if (convert == 'd' || convert == 'i')
		len += ft_putnbr_bonus(va_arg(args, int), flags, 1, 0);
	return (len);
}

static int	ft_parse_flags(const char *format, int *index, t_flags *flags)
{
	*flags = (t_flags){false};
	while (format[*index] && ft_strchr("# +", format[*index]))
	{
		if (format[*index] == '#')
			flags->hash = true;
		else if (format[*index] == ' ')
			flags->space = true;
		else if (format[*index] == '+')
			flags->sign = true;
		(*index)++;
	}
	return (0);
}

static int	ft_parse(const char *format, va_list args)
{
	int		index;
	int		len;
	t_flags	flags;

	index = 0;
	len = 0;
	while (format && format[index])
	{
		if (format[index] == '%' && format[index + 1])
		{
			index++;
			ft_parse_flags(format, &index, &flags);
			if (ft_strchr("cspdiuxX", format[index]))
				len += ft_convert_args(format[index], flags, args);
			else if (format[index] == '%')
				len += ft_putchar('%');
		}
		else if (format[index] == '%' && !format[index + 1])
			return (-1);
		else
			len += ft_putchar(format[index]);
		index++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	va_start(args, format);
	len = ft_parse(format, args);
	va_end(args);
	return (len);
}
