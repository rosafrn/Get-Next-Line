#include "get_next_line.h"

void ft_concat(char **reference, char **line, size_t end)
{
	char *temp = NULL;

    temp = ft_strnjoin(*line, *reference, end);
	free(*line);
	*line = temp;
	//printf("END: %zu\n", end);
	//printf("REF: %s\n", *reference);
	if (reference[0][end - 1] == '\n')
	{
		temp = ft_substr(*reference, end);
		free(*reference);
		*reference = temp;
	}
	else if (reference[0][end] == '\0')
	{
		free(*reference);
		*reference = NULL;
	}
}

char *ft_read(int fd, char **reference, char **line, int *flag)
{
	size_t end;

	*reference = (char *)malloc(BUFFER_SIZE + 1);
	if (!*reference)
		return (NULL);
    end = read(fd, *reference, BUFFER_SIZE);
	if (end == 0)
	{
		free (*reference);
		*flag = *flag + 1;
		if (!*line)
			return (NULL);
		if (**line == '\0')
		{
			free (*line);
			return (NULL);
		}
		return (*line);
	}
	reference[0][end] = '\0';
	return (*reference);
}

void ft_firstcheck(char **reference, char **line)
{
		int end;

		end = 0;
    	while (reference[0][end] != '\0')
    	{
        	if (reference[0][end] == '\n')
			{
				if (!*line)
					*line = ft_strdup("");
				ft_concat(&*reference, &*line, (end + 1));
				break;
				//return (*line);	
			}
			end++;
    	}
		if (!*line)
		{
			*line = ft_strdup("");
			ft_concat(&*reference, &*line, end);
		}
		//return (NULL);
}

char *get_next_line(int fd)
{
    static char *reference = NULL;
    char *line = NULL;
    //int end = 0;
	static int flag = 0;
	
    if (fd < 0 || fd > 1024 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
        return (NULL);
    while (flag == 0)
	{
		if (reference == NULL)
		{
			reference =ft_read(fd, &reference, &line, &flag);
			if (!reference)
				return (NULL);
			if (flag == 1)
				return (reference);
		}
		// end = 0;
    	// while (reference[end] != '\0')
    	// {
        // 	if (reference[end] == '\n')
		// 	{
		// 		if (!line)
		// 			line = ft_strdup("");
		// 		ft_concat(&reference, &line, (end + 1));
		// 		return (line);	
		// 	}
		// 	end++;
    	// }
		ft_firstcheck(&reference, &line);
		if (reference != NULL)
		{
			printf("acabei aqui\n");
			return (line);
		}
		/*if (!line)
			line = ft_strdup("");
		ft_concat(&reference, &line, end);*/
	}
	return (NULL);
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
	//printf("%s", line);
}

// int main(void)
// {
// 	int fd = -4;//open("nl", O_RDONLY);

// 	printf("%s", get_next_line(fd));
// }
