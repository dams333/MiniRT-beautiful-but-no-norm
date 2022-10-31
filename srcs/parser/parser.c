/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:44:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/31 17:21:13 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_one_letter(char **elem, bool *ret, t_parsing *parsing)
{
	if (ft_strncmp(elem[0], "C", 1) == 0)
		*ret = parse_camera(elem, parsing);
	else if (ft_strncmp(elem[0], "A", 1) == 0)
		*ret = parse_ambient_lightning(elem, parsing);
	else if (ft_strncmp(elem[0], "L", 1) == 0)
		*ret = parse_light(elem, parsing);
	else
	{
		ft_putstr_fd("Error\nObject type [", 2);
		ft_putstr_fd(elem[0], 2);
		ft_putendl_fd("] unknown", 2);
		*ret = false;
	}
}

void	parse_two_letters(char **elem, bool *ret, t_parsing *parsing)
{
	if (ft_strncmp(elem[0], "sp", 2) == 0)
		*ret = parse_sphere(elem, parsing);
	else if (ft_strncmp(elem[0], "pl", 2) == 0)
		*ret = parse_plane(elem, parsing);
	else if (ft_strncmp(elem[0], "cy", 2) == 0)
		*ret = parse_cylinder(elem, parsing);
	else
	{
		ft_putstr_fd("Error\nObject type [", 2);
		ft_putstr_fd(elem[0], 2);
		ft_putendl_fd("] unknown", 2);
		*ret = false;
	}
}

bool	parse_line(char *line, t_parsing *parsing)
{
	char	**elem;
	bool	ret;

	if (ft_strchr(line, '\n'))
		line[ft_strchr(line, '\n') - line] = '\0';
	elem = ft_split(line, ' ');
	if (!elem)
		return (ft_putendl_fd("Error\nA malloc failed during parsing", 2),
			false);
	if (elem[0] == NULL)
		return (free_split(elem), false);
	ret = true;
	if (ft_strlen(elem[0]) == 1)
		parse_one_letter(elem, &ret, parsing);
	else if (ft_strlen(elem[0]) == 2)
		parse_two_letters(elem, &ret, parsing);
	else
	{
		ft_putstr_fd("Error\nObject type [", 2);
		ft_putstr_fd(elem[0], 2);
		ft_putendl_fd("] unknown", 2);
		ret = false;
	}
	free_split(elem);
	return (ret);
}

bool	read_file(int fd, t_parsing *parsing)
{
	int		res;
	char	*line;

	res = get_next_line(fd, &line, 0);
	while (line != NULL)
	{
		if (ft_strlen(line) > 1 && line[0] != '#')
		{
			if (!parse_line(line, parsing))
			{
				free(line);
				get_next_line(fd, NULL, 1);
				return (false);
			}
		}
		free(line);
		res = get_next_line(fd, &line, 0);
	}
	if (res == READ_ERROR)
		return (ft_putendl_fd("Error\nThe file cannot be read", 2), false);
	else if (res == END_OF_READ)
		return (true);
	else
		return (ft_putendl_fd("Error\nA malloc failed during parsing", 2),
			false);
}

bool	parse_map(int argc, char **argv, t_parsing *parsing)
{
	char	*file_name;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nPlease specify a file", 2);
		return (false);
	}
	file_name = argv[1];
	if (ft_strlen(file_name) < 4
		|| ft_strncmp(file_name + ft_strlen(file_name) - 3, ".rt", 3) != 0)
	{
		ft_putendl_fd("Error\nThe file is not a .rt file", 2);
		return (false);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error", 2);
		perror("The file cannot be open");
		return (false);
	}
	return (read_file(fd, parsing));
}
