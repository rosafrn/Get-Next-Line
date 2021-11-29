#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

//falta ver a opção se nao existir nova linha no buffersize, entao tem de se fazer um join)

char *get_next_line(int fd)
{
    static char *reference = NULL;
    char *substring = NULL;
    size_t end = 0;
    size_t add = 0;
    const char *newline = "\n";

    //if (fd < 0)
    //    return (NULL);
	reference = (char *)malloc(BUFFER_SIZE);
    if (reference == NULL)
        read(fd, reference, BUFFER_SIZE);
    while (reference[end] && strchr(newline, reference[end]))
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
    substring = (char *)malloc(/*end + add*/100);
    strcpy(substring, reference);
    while (*reference != *newline || *reference)
        reference++;
    return (substring);
}


int main(void)
{
	int fd;
	char *line;
	int i = 0;
	fd = open("teste.txt", O_RDONLY);
	while (i < 1)
	{
	line = get_next_line (fd);
	printf("%s" , line);
	i++;
	}
}
