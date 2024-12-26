/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:24:44 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/12 09:12:10 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	len_malloc;

	if ((nmemb > SIZE_MAX_SQRT || size > SIZE_MAX_SQRT)
		&& nmemb > 0 && (SIZE_MAX / nmemb) < size)
		return (NULL);
	len_malloc = nmemb * size;
	array = malloc(len_malloc);
	if (!array)
		return (NULL);
	ft_bzero(array, len_malloc);
	return (array);
}
