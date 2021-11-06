# define BUFF_SIZE 32
# define FD_SIZE 4865
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

size_t        ft_strlen(const char *str)
{
    size_t    c;

    c = 0;
    while (*str != '\0')
    {
        c++;
        str++;
    }
    return (c);
}

void    ft_strdel(char **as)
{
    if (as == NULL)
        return ;
    free(*as);
    *as = NULL;
}

char    *ft_strcat(char *s1, const char *s2)
{
    size_t i;

    i = ft_strlen(s1);
    while (*s2 != '\0')
    {
        s1[i++] = *s2;
        s2++;
    }
    s1[i] = '\0';
    return (s1);
}

char    *ft_strcpy(char *dst, const char *src)
{
    int i;

    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *cat;
    int        size;

    if (s1 == NULL || s2 == NULL)
        return (NULL);
    size = ft_strlen(s1) + ft_strlen(s2);
    if ((cat = (char *)malloc(sizeof(*cat) * (size + 1))) == NULL)
        return (NULL);
    cat = ft_strcpy(cat, s1);
    cat = ft_strcat(cat, s2);
    return (cat);
}

void    *ft_memset(void *b, int c, size_t len)
{
    char    *m;
    size_t    i;

    i = 0;
    if (len == 0)
        return (b);
    m = (char *)b;
    while (len > i)
    {
        m[i] = (unsigned char)c;
        i++;
    }
    return (b);
}

char    *ft_strdup(const char *s1)
{
    char *cpy;

    if ((cpy = malloc(ft_strlen(s1) + 1)) == 0)
        return (NULL);
    return (ft_strcpy(cpy, s1));
}

int        analyse_lec(char **keep, char **line)
{
    char    *tmp;
    char    *ligne;
    int        i;

    i = 0;
    ligne = *keep;
    while (ligne[i] != '\n')
    {
        i++;
        if (ligne[i] == '\0')
            return (0);
    }
    tmp = &ligne[i];
    *tmp = '\0';
    *line = ft_strdup(*keep);
    *keep = ft_strdup(tmp + 1);
    free(ligne);
    return (1);
}

int        lecture(int fd, char *buf, char **keep, char **line)
{
    int        b;
    char    *tmp;

    while ((b = read(fd, buf, BUFF_SIZE)) > 0)
    {
        buf[b] = '\0';
        if (*keep)
        {
            tmp = *keep;
            *keep = ft_strjoin(tmp, buf);
            ft_strdel(&tmp);
        }
        else
            *keep = ft_strdup(buf);
        if (analyse_lec(keep, line))
            break ;
    }
    if (b > 0)
        return (1);
    return (b);
}

int        check_error(char **line, int fd, char **keep)
{
    if (!line || (fd < 0 || fd >= FD_SIZE) || (read(fd, keep[fd], 0) < 0))
        return (-1);
    return (0);
}

int        get_next_line(int const fd, char **line)
{
    static char        *keep[FD_SIZE];
    char            *buf;
    int                b;

    if (check_error(line, fd, keep) == -1 ||
            !(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
        return (-1);
    if (keep[fd])
        if (analyse_lec(&keep[fd], line))
            return (1);
    buf = ft_memset(buf, '\0', BUFF_SIZE);
    b = lecture(fd, buf, &keep[fd], line);
    free(buf);
    if (b != 0 || keep[fd] == NULL || keep[fd][0] == '\0')
    {
        if (!b && *line)
            *line = NULL;
        return (b);
    }
    *line = keep[fd];
    keep[fd] = NULL;
    return (1);
}

int        main(int argc, char **argv)
{
    int        fd;
    char    *line;
    int        res;
    int        count;

    count = 0;
    res = 0;
    line = NULL;
    // if (argc > 0)
    // {
    //     fd_test(--argc, ++argv);
    // }
    // else
    // {
    if ((fd = open(argv[1], O_RDONLY)) > 0 && argc == 1)
    {
        while ((res = get_next_line(fd, &line)) > 0)
        {
            write(1, line, ft_strlen(line) + 1);
                write(1, "\n", 1);
            free(line);
            count++;
        }
    }
    close(fd);
    return (0);
}