/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cylindrical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:26:19 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 14:55:10 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "geometric.h"
#include "get_point_through_ray_at_time.h"
#include "get_rotation_angles.h"
#include "rotate.h"
#include "sec_degree_utils.h"
#include "structures.h"

static t_point	rotate_to_z_axis(t_point point, t_vector orientation);

static double	get_inclination(t_point point)
{
	double	inclination;

	inclination = NAN;
	if (point.x > 0)
		inclination = atan(point.y / point.x);
	if (point.x < 0 && point.y >= 0)
		inclination = atan(point.y / point.x) + M_PI;
	if (point.x < 0 && point.y < 0)
		inclination = atan(point.y / point.x) - M_PI;
	if (point.x == 0 && point.y > 0)
		inclination = M_PI_2;
	if (point.x == 0 && point.y < 0)
		inclination = -M_PI_2;
	inclination += M_PI;
	return (inclination);
}

t_cylindrical_point	to_cylindrical(t_point base, t_vector orientation,
						double radius, t_point point)
{
	t_cylindrical_point	cy_point;

	vector_substract(&point, point, base);
	point = rotate_to_z_axis(point, orientation);
	cy_point.radius = radius;
	cy_point.z = point.z;
	cy_point.azimuth = get_inclination(point);
	return (cy_point);
}

static t_point	rotate_to_z_axis(t_point point, t_vector orientation)
{
	double				x_angle;
	double				y_angle;
	t_vector			z;

	z.x = 0;
	z.y = 0;
	z.z = 1;
	x_angle = get_x_rotation_angle(orientation, z);
	rotate_around_x(&point, x_angle);
	rotate_around_x(&orientation, x_angle);
	y_angle = get_y_rotation_angle(orientation, z);
	rotate_around_y(&point, y_angle);
	return (point);
}
