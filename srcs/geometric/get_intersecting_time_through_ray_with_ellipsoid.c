/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_time_through_ray_with_el          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:25:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/03 14:32:40 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_intersecting_obj.h"
#include "get_nearest_positive_intersection.h"
#include "sec_degree_factors.h"
#include "sec_degree_utils.h"

static double	get_a(t_ray ray, t_ellipsoid ellipsoid);
static double	get_b(t_ray ray, t_ellipsoid ellipsoid);
static double	get_c(t_ray ray, t_ellipsoid ellipsoid);

double	get_intersecting_time_through_ray_with_ellipsoid(t_ray ray,
			t_ellipsoid *ellipsoid)
{
	t_sec_degree_factors	factors;
	double					t;

	factors.a = get_a(ray, *ellipsoid);
	factors.b = get_b(ray, *ellipsoid);
	factors.c = get_c(ray, *ellipsoid);
	t = get_nearest_positive_intersection(factors);
	return (t);
}

static double	get_a(t_ray ray, t_ellipsoid ellipsoid)
{
	return (1 / pow(ellipsoid.factors.a, 2) * pow(ray.vec.x, 2)
		+ 1 / pow(ellipsoid.factors.b, 2) * pow(ray.vec.y, 2)
		+ 1 / pow(ellipsoid.factors.c, 2) * pow(ray.vec.z, 2));
}

static double	get_b(t_ray ray, t_ellipsoid ellipsoid)
{
	return (2 / pow(ellipsoid.factors.a, 2) * ray.vec.x
		* (ray.base.x - ellipsoid.pos.x)
		+ 2 / pow(ellipsoid.factors.b, 2) * ray.vec.y
		* (ray.base.y - ellipsoid.pos.y)
		+ 2 / pow(ellipsoid.factors.c, 2) * ray.vec.z
		* (ray.base.z - ellipsoid.pos.z));
}

static double	get_c(t_ray ray, t_ellipsoid ellipsoid)
{
	return (1 / pow(ellipsoid.factors.a, 2)
		* pow(ray.base.x - ellipsoid.pos.x, 2)
		+ 1 / pow(ellipsoid.factors.b, 2)
		* pow(ray.base.y - ellipsoid.pos.y, 2)
		+ 1 / pow(ellipsoid.factors.c, 2)
		* pow(ray.base.z - ellipsoid.pos.z, 2) - 1);
}
