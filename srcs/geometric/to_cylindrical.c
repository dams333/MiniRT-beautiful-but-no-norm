/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cylindrical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:26:19 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/13 19:19:08 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "geometric.h"
#include "get_point_through_ray_at_time.h"
#include "sec_degree_utils.h"
#include "structures.h"

static double	get_z(t_point base, t_vector orientation, t_point point);

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
	t_ray				ray;
	double				t;

	cy_point.radius = radius;
	cy_point.z = get_z(base, orientation, point);
	t = (-orientation.x * point.x - orientation.y * point.y - orientation.z
			* point.z + orientation.x * base.x + orientation.y * base.y
			+ orientation.z * base.z) / (-orientation.x * orientation.x
			- orientation.y * orientation.y - orientation.z * orientation.z);
	ray.base = base;
	ray.vec = orientation;
	base = get_point_through_ray_at_time(ray, t);
	vector_substract(&point, point, base);
	cy_point.azimuth = get_inclination(point);
	return (cy_point);
}

static double	get_z(t_point base, t_vector orientation, t_point point)
{
	t_ray	ray;
	double	t;

	t = (-orientation.x * point.x - orientation.y * point.y - orientation.z
			* point.z + orientation.x * base.x + orientation.y * base.y
			+ orientation.z * base.z) / (-orientation.x * orientation.x
			- orientation.y * orientation.y - orientation.z * orientation.z);
	ray.base = base;
	ray.vec = orientation;
	return (calc_distance_from_ray_and_time(ray, t));
}
