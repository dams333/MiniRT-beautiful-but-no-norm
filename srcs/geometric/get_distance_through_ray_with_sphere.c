/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance_through_ray_with_sphere.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:25:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/01 14:45:08 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_intersecting_obj.h"
#include "get_nearest_positive_intersection.h"
#include "sec_degree_utils.h"

static double	get_a(t_ray ray);
static double	get_b(t_ray ray, t_sphere_object *sphere);
static double	get_c(t_ray ray, t_sphere_object *sphere);

double	get_distance_through_ray_with_sphere(t_ray ray, t_sphere_object *sphere)
{
	double	a;
	double	b;
	double	c;
	double	t;

	a = get_a(ray);
	b = get_b(ray, sphere);
	c = get_c(ray, sphere);
	t = get_nearest_positive_intersection(a, b, c);
	if (isnan(t))
		return (NAN);
	return (calc_distance_from_ray_and_time(ray, t));
}

static double	get_a(t_ray ray)
{
	return (pow(ray.vec.x, 2) + pow(ray.vec.y, 2) + pow(ray.vec.z, 2));
}

static double	get_b(t_ray ray, t_sphere_object *sphere)
{
	return (2 * (ray.vec.x * (ray.base.x - sphere->coord_x)
			+ ray.vec.y * (ray.base.y - sphere->coord_y)
			+ ray.vec.z * (ray.base.z - sphere->coord_z)));
}

static double	get_c(t_ray ray, t_sphere_object *sphere)
{
	return (pow(ray.base.x - sphere->coord_x, 2)
		+ pow(ray.base.y - sphere->coord_y, 2)
		+ pow(ray.base.z - sphere->coord_z, 2)
		- pow(sphere->diameter / 2, 2));
}
