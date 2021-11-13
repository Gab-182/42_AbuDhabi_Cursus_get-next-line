#include "get_next_line_bonus.h"
/****************************************************************/
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
/***************************************************************/