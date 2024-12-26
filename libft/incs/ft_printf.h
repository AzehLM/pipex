/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:48:29 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/05 20:01:09 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_flags
{
	bool	hash;
	bool	space;
	bool	sign;
}	t_flags;

int		ft_ptrhexa(void *ptr);
int		ft_putchar(int c);
int		ft_puthexa_lowercase_flags(unsigned long n, t_flags flags);
int		ft_puthexa_uppercase_flags(unsigned int n, t_flags flags);
int		ft_puthexa_lowercase(unsigned long n);
int		ft_putnbr_base(unsigned long nbr, char *base);
int		ft_putnbr_bonus(int n, t_flags flags, long ten_power, int count);
int		ft_putstr(char *str);
int		ft_strlen_secured(const char *s);
int		ft_unsigned_decimal(unsigned int n);

int		ft_printf(const char *format, ...)
		__attribute__((format(printf, 1, 2)));

#endif
