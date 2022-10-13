/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_l_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:55:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/13 13:38:56 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define LIGHT_ERROR_ARGS "Error\nImpossible to parse light \
because argument's count is not 4"
#define LIGHT_ERROR_RATIO "Error\nImpossible to parse light \
because lightning ratio is not in [0;1]"
#define LIGHT_ERROR_COLOR "Error\nImpossible to parse light \
because one of the color composant is not in [0;255]"
#define CYLINDER_ERROR_ARGS "Error\nImpossible to parse cylinder because \
argument's count is not 6"
#define CYLINDER_ERROR_DIAMETER "Error\nImpossible to parse cylinder because \
diameter is < 0"
#define CYLINDER_ERROR_COLOR "Error\nImpossible to parse cylinder \
because one of the color composant is not in [0;255]"
#define CYLINDER_ERROR_ORIENTATION "Error\nImpossible to parse cylinder \
becasue one composant of the orientation vector is not in [-1;1]"
#define CYLINDER_ERROR_DIAMETER "Error\nImpossible to parse cylinder because \
diameter is < 0"
#define CYLINDER_ERROR_HEIGHT "Error\nImpossible to parse cylinder because \
height is < 0"

bool	parse_light_2(t_parsing *parsing, t_light_object *obj)
{
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0
		|| obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		free(obj);
		return (ft_putendl_fd(LIGHT_ERROR_COLOR, 2), false);
	}
	if (!add_item_to_list(&(parsing->lights), obj, LIGHT))
		return (free(obj), false);
	return (true);
}

bool	parse_light(char **args, t_parsing *parsing)
{
	t_light_object	*obj;

	if (get_split_size(args) != 4)
		return (ft_putendl_fd(LIGHT_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_light_object));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_three_doubles(args[1], &(obj->coord_x), &(obj->coord_y),
			&(obj->coord_z)))
		return (free(obj), false);
	if (!parse_double(args[2], &(obj->brightness_ratio)))
		return (free(obj), false);
	if (obj->brightness_ratio < 0 || obj->brightness_ratio > 1)
	{
		free(obj);
		return (ft_putendl_fd(LIGHT_ERROR_RATIO, 2), false);
	}
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g),
			&(obj->color_b)))
		return (free(obj), false);
	return (parse_light_2(parsing, obj));
}

bool	parse_cylinder_3(char **args, t_parsing *parsing,
			t_cylinder *obj)
{
	if (!parse_textures(args, 6, &(obj->texture_infos)))
		return (free(obj), false);
	if (!add_item_to_list(&(parsing->hittables), obj, CYLINDER))
	{
		free(obj->texture_infos.normal_map_file);
		free(obj->texture_infos.texture_file);
		return (free(obj), false);
	}
	obj->bump_map.img = NULL;
	return (true);
}

bool	parse_cylinder_2(char **args, t_parsing *parsing,
			t_cylinder *obj)
{
	if (obj->diameter < 0)
	{
		free(obj);
		return (ft_putendl_fd(CYLINDER_ERROR_DIAMETER, 2), false);
	}
	if (!parse_double(args[4], &(obj->height)))
		return (free(obj), false);
	if (obj->height < 0)
	{
		free(obj);
		return (ft_putendl_fd(CYLINDER_ERROR_HEIGHT, 2), false);
	}
	if (!parse_three_ints(args[5], &(obj->color_r), &(obj->color_g),
			&(obj->color_b)))
		return (free(obj), false);
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0
		|| obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		free(obj);
		return (ft_putendl_fd(CYLINDER_ERROR_COLOR, 2), false);
	}
	return (parse_cylinder_3(args, parsing, obj));
}

bool	parse_cylinder(char **args, t_parsing *parsing)
{
	t_cylinder	*obj;

	if (get_split_size(args) != 6 && get_split_size(args) != 8
		&& get_split_size(args) != 10)
		return (ft_putendl_fd(CYLINDER_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_cylinder));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_three_doubles(args[1], &(obj->pos.x), &(obj->pos.y),
			&(obj->pos.z)))
		return (free(obj), false);
	if (!parse_three_doubles(args[2], &(obj->orientation.x),
			&(obj->orientation.y), &(obj->orientation.z)))
		return (free(obj), false);
	if (obj->orientation.x < -1 || obj->orientation.x > 1
		|| obj->orientation.y < -1 || obj->orientation.y > 1
		|| obj->orientation.z < -1 || obj->orientation.z > 1)
	{
		free(obj);
		return (ft_putendl_fd(CYLINDER_ERROR_ORIENTATION, 2), false);
	}
	if (!parse_double(args[3], &(obj->diameter)))
		return (free(obj), false);
	return (parse_cylinder_2(args, parsing, obj));
}
