/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:44:14 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/13 10:44:17 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_reading_buffer(int fd, char *edited_buffer)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while ((ft_strchr(edited_buffer, '\n') == NULL && (bytes != 0)))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		edited_buffer = ft_strjoin(edited_buffer, buffer);
	}
	free(buffer);
	return (edited_buffer);
}

char	*ft_search_new_line(char *edited_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!edited_buffer[i])
		return (NULL);
	while (edited_buffer[i] != '\n' && edited_buffer[i] != '\0')
		i++;
	line = (char *) malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (edited_buffer[i] && edited_buffer[i] != '\n')
	{
		line[i] = edited_buffer[i];
		i++;
	}
	if (edited_buffer[i] == '\n')
	{
		line[i] = edited_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_next_text(char *edited_buffer)
{
	int		i;
	int		n;
	char	*next_text;

	i = 0;
	n = 0;
	while (edited_buffer[i] && edited_buffer[i] != '\n')
		i++;
	if (!edited_buffer[i])
	{
		free(edited_buffer);
		return (NULL);
	}
	next_text = (char *)malloc(sizeof(char)
			* (ft_strlen(edited_buffer) - i + 1));
	if (!next_text)
		return (NULL);
	i++;
	while (edited_buffer[i])
		next_text[n++] = edited_buffer[i++];
	next_text[n] = '\0';
	free(edited_buffer);
	return (next_text);
}

char	*get_next_line(int fd)
{
	static char		*edited_buffer[256];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	edited_buffer[fd] = ft_reading_buffer(fd, edited_buffer[fd]);
	if (!edited_buffer[fd])
		return (NULL);
	line = ft_search_new_line(edited_buffer[fd]);
	edited_buffer[fd] = ft_get_next_text(edited_buffer[fd]);
	return (line);
}
