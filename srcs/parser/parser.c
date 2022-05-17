/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:44:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/17 13:45:15 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_line(char *line)
{
	char	**elem;

	elem = ft_split(line, ' ');
	if (!elem)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!elem[0])
		return (0);
	if (ft_strlen(elem[0]) == 1)
	{
		if(ft_strncmp(elem[0], "C", 1) == 0)
		{
			return (parse_camera(elem));
		}
		else if(ft_strncmp(elem[0], "A", 1) == 0)
		{

		}
		else if(ft_strncmp(elem[0], "L", 1) == 0)
		{
			
		}
		else
		{
			ft_putstr_fd("Error\nObject type ", 2);
			ft_putstr_fd(elem[0], 2);
			ft_putendl_fd(" unknown", 2);
			return (false);
		}
	}
	else if (ft_strlen(elem[0]) == 2)
	{
		if(ft_strncmp(elem[0], "sp", 2) == 0)
		{

		}
		else if(ft_strncmp(elem[0], "pl", 2) == 0)
		{

		}
		else if(ft_strncmp(elem[0], "cy", 2) == 0)
		{
			
		}
		else
		{
			ft_putstr_fd("Error\nObject type ", 2);
			ft_putstr_fd(elem[0], 2);
			ft_putendl_fd(" unknown", 2);
			return (false);
		}
	}
	else
	{
		ft_putstr_fd("Error\nObject type ", 2);
		ft_putstr_fd(elem[0], 2);
		ft_putendl_fd(" unknown", 2);
		return (false);
	}
	return (true);
}

int	read_file(int fd)
{
	int		res;
	char	*line;

	res = get_next_line(fd, &line);
	while (line != NULL)
	{
		if (ft_strlen(line) > 1)
		{
			if(!parse_line(line))
				return (1);
		}
		free(line);
		res = get_next_line(fd, &line);
	}
	if (res == READ_ERROR)
	{
		ft_putendl_fd("Error", 2);
		perror("The file cannot be read");
		return (1);
	}
	else if (res == END_OF_READ)
	{
		ft_putendl_fd("End of parsing !", 1);
		return (0);
	}
	else
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (1);
	}
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
