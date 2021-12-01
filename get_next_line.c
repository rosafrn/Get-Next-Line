#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

 !!! ESTAS A USAR A FUNCAO STRLEN ORIGINAL - MUDA PARA FT_STRLEN
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
    static char *reference = '\0';
    char *substring = "";
    size_t end = 0;
	static char flag[] = "0";
	
	// verificar se o ficheiro existe OU se a referencia aponta para o final do ficheiro
    if (fd < 0)
        return (0);
	
	// ler o ficheiro SE o conteudo da referencia for o NULL
    if (*reference == '\0')
	{
		//apagar o conteudo da referencia e atribuir novo valor
		free(reference);
		reference = (char *)malloc(BUFFER_SIZE);
		if (!reference)
			return (0);
        end = read(fd, reference, BUFFER_SIZE);
		//se estivermos no final do ficheiro mudar o valor da flag
		if (end != BUFFER_SIZE)
			*flag = '1';
		reference[end] = '\0';
	}

	//enquanto nao chegar ao final do ficheiro
	end = 0;
    while (reference[end] != '\0')
    {
		//se encontrar uma quebra de libra
        if (reference[end] == '\n' || reference[end + 1] == '\0')
		{
            substring = ft_strjoin(substring, reference);
			if (reference[end + 1] == '\0' && *flag != 1) 
				//ler outra vez o ficheiro
			else
				reference = reference + (end + 1);
			return (substring);
		}
		end++;
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
