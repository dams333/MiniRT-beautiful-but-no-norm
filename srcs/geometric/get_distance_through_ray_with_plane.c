/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance_through_ray_with_plane.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:25:21 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/23 14:24:53 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_intersecting_obj.h"

static double	get_numerator(t_ray ray, t_plane_object *plane);
static double	get_denominator(t_ray ray, t_plane_object *plane);

double	get_distance_through_ray_with_plane(t_ray ray,
			t_plane_object *plane)
{
	double	numerator;
	double	denominator;
	double	t;
	t_point	intersection;

	numerator = get_numerator(ray, plane);
	denominator = get_denominator(ray, plane);
	if (numerator == 0 && denominator == 0)
		return (0.0);
	if (denominator == 0)
		return (NAN);
	t = numerator / denominator;
	intersection.x = ray.vec.x * t + ray.base.x;
	intersection.y = ray.vec.y * t + ray.base.y;
	intersection.z = ray.vec.z * t + ray.base.z;
	return (sqrt(pow(intersection.x - ray.base.x, 2)
			+ pow(intersection.y - ray.base.y, 2)
			+ pow(intersection.z - ray.base.z, 2)));
}

static double	get_numerator(t_ray ray, t_plane_object *plane)
{
	return (-plane->orientation_x * ray.base.x
		- plane->orientation_y * ray.base.y
		- plane->orientation_z * ray.base.z
		- plane->d);
}

static double	get_denominator(t_ray ray, t_plane_object *plane)
{
	return (plane->orientation_x * ray.vec.x
		+ plane->orientation_y * ray.vec.y
		+ plane->orientation_z * ray.vec.z);
}
