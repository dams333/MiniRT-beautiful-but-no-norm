/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:41:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 13:58:02 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define CAMERA_ERROR_COUNT "Error\nThere is more than one camera in the scene"
#define CAMERA_ERROR_ARGS "Error\nImpossible to parse camera because \
argument's count is not 4"
#define CAMERA_ERROR_ORIENTATION "Error\nImpossible to parse camera \
because one composant of the orientation vector is not in [-1;1]"
#define CAMERA_ERROR_FOV "Error\nImpossible to parse camera because FOV \
is not in [0;180]"
#define AMBIANT_ERROR_COUNT "Error\nThere is more than one ambiant light \
in the scene"
#define AMBIANT_ERROR_ARGS "Error\nImpossible to parse ambiant light \
because argument's count is not 3"
#define AMBIANT_ERROR_RATIO "Error\nImpossible to parse ambiant light \
because lightning ratio is not in [0;1]"
#define AMBIANT_ERROR_COLOR "Error\nImpossible to parse ambiant light \
because one of the color composant is not in [0;255]"
#define LIGHT_ERROR_ARGS "Error\nImpossible to parse light \
because argument's count is not 4"
#define LIGHT_ERROR_RATIO "Error\nImpossible to parse light \
because lightning ratio is not in [0;1]"
#define LIGHT_ERROR_COLOR "Error\nImpossible to parse light \
because one of the color composant is not in [0;255]"

bool	parse_camera_2(char **args, t_parsing *parsing, t_camera_object *obj)
{
	if (!parse_int(args[3], &(obj->horizontal_fov)))
		return (free(obj), false);
	if (obj->horizontal_fov < 0 || obj->horizontal_fov > 180)
	{
		free(obj);
		return (ft_putendl_fd(CAMERA_ERROR_FOV, 2), false);
	}
	parsing->camera = obj;
	return (true);
}

bool	parse_camera(char **args, t_parsing *parsing)
{
	t_camera_object	*obj;

	if (parsing->camera != NULL)
		return (ft_putendl_fd(CAMERA_ERROR_COUNT, 2), false);
	if (get_split_size(args) != 4)
		return (ft_putendl_fd(CAMERA_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_camera_object));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_three_doubles(args[1], &(obj->coord_x), &(obj->coord_y),
			&(obj->coord_z)))
		return (free(obj), false);
	if (!parse_three_doubles(args[2], &(obj->orientation_x),
			&(obj->orientation_y), &(obj->orientation_z)))
		return (free(obj), false);
	if (obj->orientation_x < -1 || obj->orientation_x > 1
		|| obj->orientation_y < -1 || obj->orientation_y > 1
		|| obj->orientation_z < -1 || obj->orientation_z > 1)
	{
		free(obj);
		return (ft_putendl_fd(CAMERA_ERROR_ORIENTATION, 2), false);
	}
	return (parse_camera_2(args, parsing, obj));
}

bool	parse_ambien_lightning_2(t_parsing *parsing,
			t_ambient_lightning_object *obj)
{
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0
		|| obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		free(obj);
		return (ft_putendl_fd(AMBIANT_ERROR_COLOR, 2), false);
	}
	parsing->ambient_lightning = obj;
	return (true);
}

bool	parse_ambient_lightning(char **args, t_parsing *parsing)
{
	t_ambient_lightning_object	*obj;

	if (parsing->ambient_lightning != NULL)
		return (ft_putendl_fd(AMBIANT_ERROR_COUNT, 2), false);
	if (get_split_size(args) != 3)
		return (ft_putendl_fd(AMBIANT_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_ambient_lightning_object));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_double(args[1], &(obj->lightning_ratio)))
		return (free(obj), false);
	if (obj->lightning_ratio < 0 || obj->lightning_ratio > 1)
	{
		free(obj);
		return (ft_putendl_fd(AMBIANT_ERROR_RATIO, 2), false);
	}
	if (!parse_three_ints(args[2], &(obj->color_r), &(obj->color_g),
			&(obj->color_b)))
		return (free(obj), false);
	return (parse_ambien_lightning_2(parsing, obj));
}
