#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

//esta função aloca memoria para a string s1 e atribui o valor ""
char * ft_strdup(const char *s)
{
	char *str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = *s;
	str[1] = '\0';
	return(str);
}

//esta função cria uma substring de s iniciando no index i passado como parametro
char *ft_substr(char *s, size_t i)
{
	char *str;
	size_t x = 0;

	if (!s)
		return (0);
	str = malloc(sizeof(char) * ((strlen(s) - i) +1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[x] = s[i];
		x++;
		i++;
	}
	//printf("%s\n", reference);
	str[x] = '\0';
	//printf("%s\n", str);
	return(str);


}
//esta função concatena s1 com n bytes de s2
char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*new;
	size_t		i;
	size_t		j;

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
	while (j != n)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}


char *get_next_line(int fd)
{
    static char *reference = NULL;
    char *substring;
	char *temp;
    size_t end = 0;
	static int flag = 0;
	
	substring = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 )
        return (NULL);
    while (flag == 0)
	{
		if (reference == NULL)
		{
			reference = (char *)malloc(BUFFER_SIZE + 1);
			if (!reference)
				return (0);
        	end = read(fd, reference, BUFFER_SIZE);
			if (end == 0)
			{
				free (reference);
				flag = flag + 1;
				return (substring);
			}
			reference[end] = '\0';
		}
		end = 0;
    	while (reference[end] != '\0')
    	{
        	if (reference[end] == '\n')
			{
				if (!substring)
					substring = ft_strdup("");
           		temp = ft_strnjoin(substring, reference, (end + 1));
				free(substring);
				substring = temp;
				temp = ft_substr(reference, (end + 1));
				free(reference);
				reference = temp;
				return (substring);	
			}
			end++;
    	}
		if (!substring)
			substring = ft_strdup("");
		temp = ft_strnjoin(substring, reference, end);
		free(substring);
		substring = temp;
		free(reference);
		reference = NULL;
	}
	return (NULL);
}

// int main(void)
// {
// 	int fd;
// 	char *line;
// 	int i = 0;
// 	fd = open("texto.txt", O_RDONLY);
// 	while (i < 2)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s" , line);
// 		i++;
// 	}
// 	//printf("%s", line);
// }
