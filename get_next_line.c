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

void	ft_concat(char **reference, char **line, size_t end)
{
	char	*temp;

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

char	*ft_read(int fd, char **reference, char **line, int *flag)
{
	int	end;

	*reference = (char *)malloc(BUFFER_SIZE + 1);
	if (!*reference)
		return (NULL);
	end = read(fd, *reference, BUFFER_SIZE);
	if (end == 0)
	{
		free (*reference);
		*flag = *flag + 1;
		if (!*line || **line == '\0')
		{
			free(*line);
			return (NULL);
		}	
		return (*line);
	}
	if (end < 0)
	{
		free (*reference);
		return (NULL);
	}
	reference[0][end] = '\0';
	return (*reference);
}

void	blabla(char **reference, char **line)
{
	int	end;

	end = 0;
	while ((*reference)[end] != '\0')
	{
		if ((*reference)[end] == '\n')
		{
			if (!(*line))
				*line = ft_strdup("");
			ft_concat(&*reference, &*line, (end + 1));
			end = -1;
			break ;
		}
		end++;
	}
	if (end != -1)
	{
		if (!(*line))
			*line = ft_strdup("");
		ft_concat(&*reference, &*line, end);
	}
}

char	*get_next_line(int fd)
{
	static char	*reference = NULL;
	char		*line;
	static int	flag = 0;

	line = NULL;
	if (fd < 0 || fd > 1024 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	while (flag == 0)
	{
		if (reference == NULL)
		{
			reference = ft_read(fd, &reference, &line, &flag);
			if (!reference)
				return (NULL);
			if (flag == 1)
				return (reference);
		}
		blabla(&reference, &line);
		if (reference != NULL)
			return (line);
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

