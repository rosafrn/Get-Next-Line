#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

// !!! ESTAS A USAR A FUNCAO STRLEN ORIGINAL - MUDA PARA FT_STRLEN
//
//
//

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new = (char *)malloc(strlen(s1) + strlen(s2) + 1 * sizeof(char));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
char *get_next_line(int fd)
{
	const char *newline = "\n";
    static char *reference = "\n";
    char *substring = "";
    size_t end = 0;
    //size_t add = 0;
	int 	r = 0;
	
    if (fd < 0)
        return (NULL);
    if (reference == newline)
	{
		reference = (char *)malloc(BUFFER_SIZE + 1);
		if (!reference)
			return (0);
        r = read(fd, reference, BUFFER_SIZE);
		reference[r] = '\0';
	}
    while (reference[end])
    {
        end++;
        if (end == BUFFER_SIZE || reference[end] == '\n')
        {
            ft_strjoin(substring, reference);
			//free (reference);
			reference = (char *)malloc(BUFFER_SIZE + 1);
			if (!reference)
				return (0);
			r = read(fd, reference, BUFFER_SIZE);
			reference[r] = '\0';
        }
    }
    ft_strjoin(substring, reference);
    while (*reference != *newline)
	{
        reference++;
		if (reference == NULL)
			return (0);
	}
    return (substring);
}

int main(void)
{
	int fd;
	char *line;
	int i = 0;
	fd = open("texto.txt", O_RDONLY);
	while (i < 1)
	{
		line = get_next_line(fd);
		printf("%s" , line);
		i++;
	}
}
