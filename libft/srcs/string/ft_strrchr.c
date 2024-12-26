/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:01:30 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/08 12:33:00 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*str;

	str = (char *) s;
	len = ft_strlen(str);
	if (c == '\0')
		return (&str[len]);
	while (len > 0 && str[len] != (char) c)
		len--;
	if (str[len] == (char) c)
		return (&str[len]);
	return (NULL);
}
