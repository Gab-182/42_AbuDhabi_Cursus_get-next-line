#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main()
{
	int		fd;
	char	*str;
	
	fd = open("buzz", O_RDONLY);
	str = get_next_line(fd);

	while(str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}