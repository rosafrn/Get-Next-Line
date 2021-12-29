/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosferna <rosferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:36:49 by rosferna          #+#    #+#             */
/*   Updated: 2021/12/29 17:37:53 by rosferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//esta função aloca memoria para a string s1 e atribui o valor ""
char	*ft_strdup(const char *s)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = *s;
	str[1] = '\0';
	return (str);
}

//esta função cria uma substring de s
//  iniciando no index i passado como parametro
char	*ft_substr(char *s, size_t i)
{
	char	*str;
	size_t	x;

	x = 0;
	if (!s)
		return (0);
	str = malloc(sizeof(char) * ((strlen(s) - i) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[x] = s[i];
		x++;
		i++;
	}
	str[x] = '\0';
	return (str);
}

//esta função concatena s1 com n bytes de s2
char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*new;
	size_t	i;
	size_t	j;

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
