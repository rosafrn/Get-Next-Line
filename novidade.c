#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

//esta função concatena s1 com n bytes de s2
char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	new = (char *)malloc(i + n + 1 * sizeof(char));
	if (!new)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j != (int)n)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char *get_next_line(int fd)
{
	static char *reference = "\0";
	//char *buff;
    char *substring = "";
    size_t end = 0;
	char *temp;
	
    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
	//substring = (char *)malloc(sizeof(char) *2);
    while (reference[end] != 18)
	{
		if (*reference == '\0')
		{
			reference = (char *)malloc(BUFFER_SIZE + 1);
			if (!reference)
				return (NULL);
        	end = read(fd, reference, BUFFER_SIZE);
			if (end == 0)
			{
				reference[end] = 18;
				return (substring);
			}
			reference[end] = '\0';
		}
		end = 0;
    	while (reference[end] != '\0')
    	{
        	if (reference[end] == '\n')
			{

           		temp = ft_strnjoin(substring, reference, (end + 1));
				//free (substring);
				substring = temp;
				reference = reference + (end + 1);
				return (substring);	
			}
			end++;
    	}
		temp = ft_strnjoin(substring, reference, (end + 1));
		//free (substring);
		substring = temp;
		reference = reference + end;
	}
	//free(substring);
	return (NULL);
}

// int main(void)
// {
// 	int fd;
// 	char *line;
// 	int i = 0;
// 	fd = open("texto.txt", O_RDONLY);
// 	while (i < 9)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s" , line);
// 		i++;
// 	}
// 	printf("%s", line);
// }