/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:40:00 by gueberso          #+#    #+#             */
/*   Updated: 2024/12/22 18:33:03 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr_secured(buffer, 0, i);
	return (line);
}

char	*clean_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		buffer[0] = '\0';
		return (NULL);
	}
	i++;
	new_buffer = malloc(sizeof(char) * (ft_strlen_gnl(buffer + i) + 1));
	if (!new_buffer)
		return (NULL);
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	return (new_buffer);
}

char	*read_file(int fd, char *buffer, int bytes_read)
{
	char	*temp;
	char	*old_buffer;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (free(buffer), NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		old_buffer = buffer;
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (NULL);
		free(old_buffer);
		if (!buffer || ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(temp), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	char		*old_buffer;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd], 1);
	if (!buffer[fd] || buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	old_buffer = buffer[fd];
	buffer[fd] = clean_buffer(buffer[fd]);
	free(old_buffer);
	if (ft_strlen_gnl(buffer[fd]) == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
