#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//falta ver a opção se nao existir nova linha no buffersize, entao tem de se fazer um join)

char *get_next_line(int fd)
{
    static char *reference = NULL;
    char *substring = NULL;
    size_t end = 0;
    size_t add = 0;
    const char *newline = "\n";

    if (fd < 0)
        return (NULL);
    if (reference == NULL)
        read(fd, reference, BUFFER_SIZE);
    while (strchr(newline, reference[end]))
    {
        end++;
        if (end == BUFFER_SIZE)
        {
            substring = (char *)malloc(end);
            strncpy(substring, reference, end);
            read(fd, reference, BUFFER_SIZE);
            add = end;
            end = 0;
        }
    }
    substring = (char *)malloc(end + add);
    strcat(substring, reference);
    while (*reference != *newline || *reference)
        reference++;
    return (substring);
}

int main ()
{
    int fd;
	char *line;
	fd = open("testi", 1);
	line = get_next_line (fd);
	printf("%s\n" , line);
}
