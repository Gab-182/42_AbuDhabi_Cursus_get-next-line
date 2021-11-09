#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 5

int main() 
{
    int		fd;
    int i;
    ssize_t bytes;
    char buffer[BUFFER_SIZE];
	
	fd = open("buzz.txt", O_RDONLY);

    bytes = read(fd, buffer, BUFFER_SIZE);
    // printf("fd = %d\n ", fd);
    // printf("%s\n", buffer);

    i = 0;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);

        if (bytes == -1)
        {
            printf("Error");
            break ;
        }
        
        /* Trying to check if I reached the end of the file */
        while (i < BUFFER_SIZE)
        {
            if (buffer[i] == '\n')
            {
                printf("That is a new line");
            }
            if (buffer[i] == '\0')
            {
                printf("You have reached the EOF");
                break ;
            }
            i++;
        }
        printf("%s\n", buffer);
    }
    close(fd);
    return (EXIT_SUCCESS);
}