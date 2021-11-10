#include "get_next_line.h"

char	*ft_search_new_line(char *buffer)
{
	char	*keep;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	keep = (char *) malloc(sizeof(char) * (i + 2));
	if (!keep)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		keep[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		keep[i] = buffer[i];
		i++;
	}
	keep[i] = '\0';
	return (keep);
}

char	*ft_reading_buffer(int fd, char *edited_buffer)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while ((!ft_strchr(edited_buffer, '\n') && (bytes != 0)))
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

char	*ft_get_next_text(char *edited_buffer)
{
	int		i;
	int		n;
	char	*next_text;

	i = 0;
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
	n = 0;
	while (edited_buffer[i])
		next_text[n++] = edited_buffer[i++];
	next_text[n] = '\0';
	free(edited_buffer);
	return (next_text);
}

char	*get_next_line(int fd)
{
	static char		*edited_buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	edited_buffer = ft_reading_buffer(fd, edited_buffer);
	if (!edited_buffer)
		return (NULL);
	line = ft_search_new_line(edited_buffer);
	edited_buffer = ft_get_next_text(edited_buffer);
	return (line);
}