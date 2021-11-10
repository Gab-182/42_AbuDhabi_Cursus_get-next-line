#include "get_next_line.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	
	fd = open("buzz", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	close(fd);
	
	return (0);
}
