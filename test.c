#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1

int main() 
{
    int		fd;
    int i;
    ssize_t bytes;
    char buffer[BUFFER_SIZE];
	
	fd = open("buzz", O_RDONLY);

    bytes = read(fd, buffer, BUFFER_SIZE);
    while (bytes > 0)
    {
        /* Protection*/
        if (bytes == 0 || bytes < 0)
            break;

        printf("%s\n", buffer);

        /* 
         *Trying to check if I reached the end of the file 
         * or new line found
         */
        i = 0;
        while (i <= BUFFER_SIZE)
        {
            if (buffer[i] == '\n')
            {
                printf("new line");
                i++;
            }
            else if (buffer[i] == '\0')
                {
                    printf("EOF");
                    i++;
                }
            else
            {
                i++;
            }
        }
        i = 0;
        /* Protection*/
        if (bytes == 0 || bytes < 0)
            break;
        bytes = read(fd, buffer, BUFFER_SIZE);
    }
    if (bytes <= 0)
    {
        if (bytes < 0)
            printf("Error");
        if (bytes == 0)
            printf("EOF");
    }
    close(fd);
    return (EXIT_SUCCESS);
}
