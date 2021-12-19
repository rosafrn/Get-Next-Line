/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:21:49 by rosferna          #+#    #+#             */
/*   Updated: 2021/12/19 18:21:59 by rosferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void ft_read(char **reference, char **line, size_t end)
{
	char *temp = NULL;

    temp = ft_strnjoin(*line, *reference, end);
	free(*line);
	*line = temp;
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

char *get_next_line(int fd)
{
    static char *reference = NULL;
    char *line = NULL;
    int end = 0;
	static int flag = 0;
	
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (flag == 0)
	{
		if (reference == NULL)
		{
			reference = (char *)malloc(BUFFER_SIZE + 1);
			if (!reference)
				return (NULL);
        	end = read(fd, reference, BUFFER_SIZE);
			if (end == 0)
			{
				free (reference);
				flag = flag + 1;
				if (!line)
					return (NULL);
				if (*line == '\0')
				{
					free (line);
					return (NULL);
				}
				return (line);
			}
			if (end < 0)
			{
				free (reference);
				return (NULL);
			}
			reference[end] = '\0';
		}
		end = 0;
    	while (reference[end] != '\0')
    	{
        	if (reference[end] == '\n')
			{
				if (!line)
					line = ft_strdup("");
				ft_read(&reference, &line, (end + 1));
				return (line);	
			}
			end++;
    	}
		if (!line)
			line = ft_strdup("");
		ft_read(&reference, &line, end);
	}
	return (NULL);
}

// int main(void)
// {
// 	int fd;
// 	char *line;
// 	int i = 0;
// 	fd = open("texto.txt", O_RDONLY);
// 	while (i < 6)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s" , line);
// 		i++;
// 	}
// 	//printf("%s", line);
// }

// int main(void)
// {
// 	int fd = -4;//open("nl", O_RDONLY);

// 	printf("%s", get_next_line(fd));
// }

