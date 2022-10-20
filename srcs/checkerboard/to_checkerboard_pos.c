/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_checkerboard_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:57:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/20 13:31:11 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "checkerboard.h"
#include "rotate.h"

static t_point2d	to_checkerboard_pos_from_cylinder(t_cylinder *cylinder,
						t_point point);
static t_point2d	to_checkerboard_pos_from_sphere(t_point center,
						t_point point);
static t_point2d	to_checkerboard_pos_from_plane(t_point point,
						t_vector orientation);
static t_point2d	to_checkerboard_pos_from_ellipsoid(t_ellipsoid *ellipsoid,
						t_point point);

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
	else if (obj->type == PLANE)
		board_pos = to_checkerboard_pos_from_plane(intersection,
				((t_plane *) obj->specific_object)->orientation);
	else if (is_cap)
		board_pos = to_checkerboard_pos_from_plane(intersection,
				((t_cylinder *) obj->specific_object)->orientation);
	else if (obj->type == ELLIPSOID)
		board_pos = to_checkerboard_pos_from_ellipsoid(
				((t_ellipsoid *)obj->specific_object), intersection);
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

static t_point2d	to_checkerboard_pos_from_plane(t_point point,
						t_vector orientation)
{
	t_point2d	board_point;

	point = rotate_to_z_axis(point, orientation);
	board_point.x = point.x - (int) point.x * 2;
	board_point.y = point.y - (int) point.y * 2;
	if (board_point.x < 0.0)
		board_point.x = 2 + board_point.x;
	if (board_point.y < 0.0)
		board_point.y = 2 + board_point.y;
	return (board_point);
}

static t_point2d	to_checkerboard_pos_from_ellipsoid(t_ellipsoid *ellipsoid,
						t_point point)
{
	t_point2d			board_point;
	t_ellipsoidal_point	el_point;

	el_point = to_ellipsoidal(*ellipsoid, point);
	board_point.x = el_point.longitude / (2 * M_PI);
	board_point.y = el_point.lattitude / (M_PI);
	return (board_point);
}
