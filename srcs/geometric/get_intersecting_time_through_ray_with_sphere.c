/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_time_through_ray_with_sphere      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:25:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 21:06:43 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_intersecting_obj.h"
#include "get_nearest_positive_intersection.h"
#include "sec_degree_factors.h"
#include "sec_degree_utils.h"

static double	get_a(t_ray ray);
static double	get_b(t_ray ray, t_sphere *sphere);
static double	get_c(t_ray ray, t_sphere *sphere);

double	get_intersecting_time_through_ray_with_sphere(t_ray ray,
			t_sphere *sphere)
{
	t_sec_degree_factors	factors;
	double					t;

	factors.a = get_a(ray);
	factors.b = get_b(ray, sphere);
	factors.c = get_c(ray, sphere);
	t = get_nearest_positive_intersection(factors);
	return (t);
}

static double	get_a(t_ray ray)
{
	return (pow(ray.vec.x, 2) + pow(ray.vec.y, 2) + pow(ray.vec.z, 2));
}

static double	get_b(t_ray ray, t_sphere *sphere)
{
	return (2 * (ray.vec.x * (ray.base.x - sphere->pos.x)
			+ ray.vec.y * (ray.base.y - sphere->pos.y)
			+ ray.vec.z * (ray.base.z - sphere->pos.z)));
}

static double	get_c(t_ray ray, t_sphere *sphere)
{
	return (pow(ray.base.x - sphere->pos.x, 2)
		+ pow(ray.base.y - sphere->pos.y, 2)
		+ pow(ray.base.z - sphere->pos.z, 2)
		- pow(sphere->diameter / 2, 2));
}
