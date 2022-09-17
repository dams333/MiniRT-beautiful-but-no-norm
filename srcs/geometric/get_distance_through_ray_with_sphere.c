/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance_through_ray_with_sphere.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:25:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/17 15:51:50 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "get_intersecting_obj.h"
#include "sec_degree_utils.h"

static double	get_a(t_ray ray, t_sphere_object *sphere);
static double	get_b(t_ray ray, t_sphere_object *sphere);
static double	get_c(t_ray ray, t_sphere_object *sphere);
static double	get_nearest_positive_intersection(double a, double b, double c);

double	get_distance_through_ray_with_sphere(t_ray ray, t_sphere_object *sphere)
{
	double	a;
	double	b;
	double	c;
	double	t;
	t_point	intersection;

	a = get_a(ray, sphere);
	b = get_b(ray, sphere);
	c = get_c(ray, sphere);
	t = get_nearest_positive_intersection(a, b, c);
	intersection.x = ray.vec.x * t + ray.base.x;
	intersection.y = ray.vec.y * t + ray.base.y;
	intersection.z = ray.vec.z * t + ray.base.z;
	return (sqrt(pow(intersection.x, 2)
		+ pow(intersection.y, 2)
		+ pow(intersection.z, 2)));
}

static double	get_a(t_ray ray, t_sphere_object *sphere)
{
	return (pow(ray.vec.x, 2) + pow(ray.vec.y, 2) + pow(ray.vec.z, 2));
}

static double	get_b(t_ray ray, t_sphere_object *sphere)
{
	return (2 * (ray.vec.x * (ray.point.x - sphere.x)
		+ ray.vec.y * (ray.point.y - sphere.y)
		+ ray.vec.z * (ray.point.z - sphere.z)));
}

static double	get_c(t_ray ray, t_sphere_object *sphere)
{
	return (pow(ray.point.x - sphere.x, 2)
		+ pow(ray.point.y - sphere.y, 2)
		+ pow(ray.point.z - sphere.z 2)
		- pow(sphere.diameter / 2, 2));
}

static double	get_nearest_positive_intersection(double a, double b, double c)
{
	double	first_root;
	double	second_root;

	first_root = get_first_root(a, b, c);
	second_root = get_second_root(a, b, c);
	if (isnan(first_root) || (first_root < 0 && second_root < 0))
		return (-1);
	if (first_root > 0 && first_root < second_root)
		return (first_root);
	else
		return (second_root);
}
