/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:03 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/17 19:20:48 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define TEXTURE_DUPLICATE_ERROR "Error\nYou can only have \
1 texture or checkerboard per object"
#define NORMAL_MAP_DUPLICATE_ERROR "Error\nYou can only have \
1 normal map per object"
#define CHECKERBOARD_ERROR_ARGS "Error\nImpossible to parse \
checkerboard because argument's count is not 3"
#define CHECKERBOARD_ERROR_HEIGHT "Error\nImpossible to parse \
checkerboard because height is < 0"
#define CHECKERBOARD_ERROR_WIDTH "Error\nImpossible to parse \
checkerboard because width is < 0"
#define CHECKERBOARD_ERROR_COLOR "Error\nImpossible to parse \
checkerboard because one of the color composant is not in [0;255]"

bool	parse_checkerboard_2(char **elem, t_checkerboard *checkerboard)
{
	if (parse_int(elem[1], &checkerboard->width) == false)
		return (free_split(elem), false);
	if (checkerboard->width < 0)
		return (free_split(elem), ft_putendl_fd(CHECKERBOARD_ERROR_WIDTH, 2),
			false);
	if (parse_three_ints(elem[2], &checkerboard->color_r,
			&checkerboard->color_g, &checkerboard->color_b) == false)
		return (free_split(elem), false);
	if (checkerboard->color_r < 0 || checkerboard->color_r > 255
		|| checkerboard->color_g < 0 || checkerboard->color_g > 255
		|| checkerboard->color_b < 0 || checkerboard->color_b > 255)
		return (free_split(elem), ft_putendl_fd(CHECKERBOARD_ERROR_COLOR, 2),
			false);
	free_split(elem);
	return (true);
}

bool	parse_checkerboard(char	*value, t_checkerboard *checkerboard)
{
	char	**elem;

	elem = ft_split(value, ';');
	if (!elem)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (get_split_size(elem) != 3)
		return (free_split(elem), ft_putendl_fd(CHECKERBOARD_ERROR_ARGS, 2),
			false);
	if (parse_int(elem[0], &checkerboard->height) == false)
		return (free_split(elem), false);
	if (checkerboard->height < 0)
		return (free_split(elem), ft_putendl_fd(CHECKERBOARD_ERROR_HEIGHT, 2),
			false);
	return (parse_checkerboard_2(elem, checkerboard));
}

bool	parse_texture_element_2(t_texture_infos *texture_infos,
	char *type, char *value)
{
	if (ft_strlen(type) == 10 && ft_strncmp(type, "normal_map", 10) == 0)
	{
		if (texture_infos->normal_map_file)
			return (ft_putendl_fd(NORMAL_MAP_DUPLICATE_ERROR, 2), false);
		texture_infos->normal_map_file = ft_strdup(value);
		if (!texture_infos->normal_map_file)
			return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	}
	else
		return (false);
	return (true);
}

bool	parse_texture_element(t_texture_infos *texture_infos,
	char *type, char *value)
{
	if (ft_strlen(type) == 12 && ft_strncmp(type, "checkerboard", 12) == 0)
	{
		if (texture_infos->texture_file
			|| texture_infos->checkerboard.width != -1)
			return (ft_putendl_fd(TEXTURE_DUPLICATE_ERROR, 2), false);
		if (!parse_checkerboard(value, &(texture_infos->checkerboard)))
			return (false);
	}
	else if (ft_strlen(type) == 7 && ft_strncmp(type, "texture", 7) == 0)
	{
		if (texture_infos->texture_file
			|| texture_infos->checkerboard.width != -1)
			return (ft_putendl_fd(TEXTURE_DUPLICATE_ERROR, 2), false);
		texture_infos->texture_file = ft_strdup(value);
		if (!texture_infos->texture_file)
			return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	}
	else
		return (parse_texture_element_2(texture_infos, type, value));
	return (true);
}

bool	parse_textures(char **args, int first, t_texture_infos *texture)
{
	texture->checkerboard.height = -1;
	texture->checkerboard.width = -1;
	texture->checkerboard.color_r = -1;
	texture->checkerboard.color_g = -1;
	texture->checkerboard.color_b = -1;
	texture->texture_file = NULL;
	texture->normal_map_file = NULL;
	if (get_split_size(args) > first)
	{
		if (!parse_texture_element(texture, args[first], args[first + 1]))
			return (false);
	}
	if (get_split_size(args) > first + 2)
	{
		if (!parse_texture_element(texture, args[first + 2], args[first + 3]))
		{
			free(texture->texture_file);
			free(texture->normal_map_file);
			return (false);
		}
	}
	return (true);
}
