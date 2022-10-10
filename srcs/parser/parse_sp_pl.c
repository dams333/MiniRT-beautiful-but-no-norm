/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:26:02 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 14:52:49 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define SPHERE_ERROR_ARGS "Error\nImpossible to parse sphere because \
argument's count is not 4"
#define SPHERE_ERROR_DIAMETER "Error\nImpossible to parse sphere because \
diameter is < 0"
#define SPHERE_ERROR_COLOR "Error\nImpossible to parse sphere \
because one of the color composant is not in [0;255]"
#define PLANE_ERROR_ARGS "Error\nImpossible to parse plane because \
argument's count is not 4"
#define PLANE_ERROR_ORIENTATION "Error\nImpossible to parse plane because \
one composant of the orientation vector is not in [-1;1]"
#define PLANE_ERROR_COLOR "Error\nImpossible to parse plane \
because one of the color composant is not in [0;255]"

bool	parse_sphere_2(char **args, t_parsing *parsing, t_sphere *obj)
{
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g),
			&(obj->color_b)))
		return (free(obj), false);
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0
		|| obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		free(obj);
		return (ft_putendl_fd(SPHERE_ERROR_COLOR, 2), false);
	}
	if (!add_item_to_list(&(parsing->hittables), obj, SPHERE))
		return (free(obj), false);
	return (true);
}

bool	parse_sphere(char **args, t_parsing *parsing)
{
	t_sphere	*obj;

	if (get_split_size(args) != 4)
		return (ft_putendl_fd(SPHERE_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_sphere));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_three_doubles(args[1], &(obj->pos.x), &(obj->pos.y),
			&(obj->pos.z)))
		return (free(obj), false);
	if (!parse_double(args[2], &(obj->diameter)))
		return (free(obj), false);
	if (obj->diameter < 0)
	{
		free(obj);
		return (ft_putendl_fd(SPHERE_ERROR_DIAMETER, 2), false);
	}
	return (parse_sphere_2(args, parsing, obj));
}

bool	parse_plane_2(char **args, t_parsing *parsing, t_plane *obj,
			t_point pos)
{
	obj->d = -obj->orientation.x * pos.x - obj->orientation.y
		* pos.y - obj->orientation.z * pos.z;
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g),
			&(obj->color_b)))
		return (free(obj), false);
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0
		|| obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		free(obj);
		return (ft_putendl_fd(PLANE_ERROR_COLOR, 2), false);
	}
	if (!add_item_to_list(&(parsing->hittables), obj, PLANE))
		return (free(obj), false);
	return (true);
}

bool	parse_plane(char **args, t_parsing *parsing)
{
	t_plane	*obj;
	t_point	point;

	if (get_split_size(args) != 4)
		return (ft_putendl_fd(PLANE_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_plane));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_three_doubles(args[1], &(point.x), &(point.y),
			&(point.z)))
		return (free(obj), false);
	if (!parse_three_doubles(args[2], &(obj->orientation.x),
			&(obj->orientation.y), &(obj->orientation.z)))
		return (free(obj), false);
	if (obj->orientation.x < -1 || obj->orientation.x > 1
		|| obj->orientation.y < -1 || obj->orientation.y > 1
		|| obj->orientation.z < -1 || obj->orientation.z > 1)
	{
		free(obj);
		return (ft_putendl_fd(PLANE_ERROR_ORIENTATION, 2), false);
	}
	return (parse_plane_2(args, parsing, obj, point));
}
