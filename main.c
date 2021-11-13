# include "get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
/************************************************************/
int	main()
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*str;
	int		i;

	fd1 = open("buzz1", O_RDONLY);
	fd2 = open("buzz2", O_RDONLY);
	fd3 = open("buzz3", O_RDONLY);
	i = 3;
	while (i != 0)
	{
		/*****__fd1__*******/
		str = get_next_line(fd1);
		printf("%s", str);
		free(str);

		/*****__fd2__******/
		str = get_next_line(fd2);
		printf("%s", str);
		free(str);
		
		/*****__fd3__******/
		str = get_next_line(fd3);
		printf("%s", str);
		free(str);
		i--;
	}

	close(fd1);
	close(fd2);
	close(fd3);

	return (EXIT_SUCCESS);
}
/*************************************************************/