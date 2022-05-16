/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:44:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/16 18:05:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	read_file(int fd)
{
	int		res;
	char	*line;

	res = get_next_line(fd, &line);
	while (res == LINE_READ)
	{

	}
	if (res == READ_ERROR)
	{
		ft_putendl_fd("Error", 2);
		perror("The file cannot be read");
		return (1);
	}
	if (res == MALLOC_ERROR)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (1);
	}
	return (0);
}

int	parse_map(int argc, char **argv)
{
	char	*file_name;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nPlease specify a file", 2);
		return (1);
	}
	file_name = argv[1];
	if (ft_strlen(file_name) < 4
		|| ft_strncmp(file_name + ft_strlen(file_name) - 3, ".rt", 3) != 0)
	{
		ft_putendl_fd("Error\nThe file is not a .rt file", 2);
		return (1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error", 2);
		perror("The file cannot be open");
		return (1);
	}
	return (read_file(fd));
}
