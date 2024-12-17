/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:29:19 by alex              #+#    #+#             */
/*   Updated: 2024/12/17 21:01:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	size = 0, pos = 0;
	int			i = 0;
	char		line[900000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	while(1)
	{
		if (pos >= size)
		{
			size = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (size <= 0)
				break;
		}
		line[i] = buffer[pos++];
		if (line[i++] == '\n')
			break;
	}
	if (i == 0)
		return(NULL);
	line[i] = 0;
	char	*result = malloc(i + 1);
	for(int x = 0; x <= i; x++)
		result[x] = line[x];
	return(result);
}
