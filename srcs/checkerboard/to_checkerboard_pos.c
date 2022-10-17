/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_checkerboard_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:57:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 15:53:32 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "checkerboard.h"

static t_point2d	to_checkerboard_pos_from_cylinder(t_cylinder *cylinder,
						t_point point);
static t_point2d	to_checkerboard_pos_from_sphere(t_point center,
						t_point point);
static t_point2d	to_checkerboard_pos_from_plane(t_point point);

t_point2d	to_checkerboard_pos(t_generic_object *obj, t_point intersection,
				int is_cap)
{
	t_point2d	board_pos;

	if (obj->type == SPHERE)
		board_pos = to_checkerboard_pos_from_sphere(
				((t_sphere *)obj->specific_object)->pos, intersection);
	else if (obj->type == CYLINDER && !is_cap)
		board_pos = to_checkerboard_pos_from_cylinder(
				((t_cylinder *)obj->specific_object), intersection);
	else if (obj->type == PLANE || is_cap)
		board_pos = to_checkerboard_pos_from_plane(intersection);
	return (board_pos);
}

static t_point2d	to_checkerboard_pos_from_sphere(t_point center,
						t_point point)
{
	t_spherical_point	sp_point;
	t_point2d			board_point;

	vector_substract(&point, point, center);
	sp_point = to_spherical(point);
	board_point.x = sp_point.azimuth / (2 * M_PI);
	board_point.y = sp_point.inclination / M_PI;
	return (board_point);
}

static t_point2d	to_checkerboard_pos_from_cylinder(t_cylinder *cylinder,
						t_point point)
{
	t_point2d			board_point;
	t_cylindrical_point	cy_point;

	cy_point = to_cylindrical(cylinder->pos, cylinder->orientation,
			cylinder->diameter / 2, point);
	board_point.x = cy_point.azimuth / (2 * M_PI);
	board_point.y = cy_point.z / cylinder->height;
	return (board_point);
}

static t_point2d	to_checkerboard_pos_from_plane(t_point point)
{
	t_point2d	board_point;

	board_point.x = point.x;
	board_point.y = point.y;
	return (board_point);
}
