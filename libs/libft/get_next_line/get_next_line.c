/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:12:01 by dhubleur          #+#    #+#             */
/*   Updated: 2021/12/05 20:39:42 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	while (s2[++j] != '\0')
		join[i++] = s2[j];
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (join);
}

int	read_and_stock(int fd, char *storage_buffer, char **str)
{
	char	*reading_buffer;
	int		readed;

	*str = NULL;
	reading_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!reading_buffer)
		return (MALLOC_ERROR);
	readed = 1;
	while (!ft_strchr(storage_buffer, '\n') && readed != 0)
	{
		if (readed == -1)
		{
			free(reading_buffer);
			return (READ_ERROR);
		}
		readed = read(fd, reading_buffer, BUFFER_SIZE);
		reading_buffer[readed] = '\0';
		storage_buffer = gnl_ft_strjoin(storage_buffer, reading_buffer);
	}
	free(reading_buffer);
	*str = storage_buffer;
	if (readed == 0)
		return (END_OF_READ);
	return (LINE_READ);
}

char	*get_line(char *storage_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage_buffer[i])
		return (NULL);
	while (storage_buffer[i] && storage_buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (storage_buffer[i] && storage_buffer[i] != '\n')
	{
		line[i] = storage_buffer[i];
		i++;
	}
	if (storage_buffer[i] == '\n')
	{
		line[i] = storage_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clear_storage(char *storage_buffer)
{
	int		i;
	int		j;
	char	*buff2;

	i = 0;
	while (storage_buffer[i] && storage_buffer[i] != '\n')
		i++;
	if (!storage_buffer[i])
	{
		free(storage_buffer);
		return (NULL);
	}
	buff2 = (char *)malloc(sizeof(char) * (ft_strlen(storage_buffer) - i + 1));
	if (!buff2)
		return (NULL);
	i++;
	j = 0;
	while (storage_buffer[i])
		buff2[j++] = storage_buffer[i++];
	buff2[j] = '\0';
	free(storage_buffer);
	return (buff2);
}

t_gnl_result	get_next_line(int fd, char **ptr, int need_to_free)
{
	char		*line;
	static char	*storage_buffer[1024];
	int			res;
	char		*str;

	if (need_to_free)
	{
		free(storage_buffer[fd]);
		storage_buffer[fd] = NULL;
		return (END_OF_READ);
	}
	*ptr = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (READ_ERROR);
	res = read_and_stock(fd, storage_buffer[fd], &str);
	storage_buffer[fd] = str;
	if (!storage_buffer[fd])
		return (res);
	line = get_line(storage_buffer[fd]);
	storage_buffer[fd] = clear_storage(storage_buffer[fd]);
	*ptr = line;
	return (res);
}
