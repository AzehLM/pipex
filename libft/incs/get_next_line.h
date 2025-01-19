/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:41:27 by gueberso          #+#    #+#             */
/*   Updated: 2025/01/19 18:37:13 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD FOPEN_MAX
# endif

size_t	ft_strlen_gnl(const char *str);

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_gnl(const char *s1, const char *s2);
char	*ft_substr_secured(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
