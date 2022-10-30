/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:46:54 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/30 18:27:46 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>

#include "geometric.h"
#include "get_intersecting_obj.h"
#include "get_point_through_ray_at_time.h"
#include "libft.h"
#include "obj_intersection.h"
#include "sec_degree_utils.h"

static double	get_distance_through_ray(t_ray ray, t_generic_object *obj);
static double	get_intersecting_time_through_ray(t_ray ray,
					t_generic_object *obj);
static t_vector	get_fake_normal(t_generic_object *obj, double t);

t_obj_intersection	get_intersecting_obj(t_ray ray, t_generic_object *objs)
{
	t_obj_intersection	obj_intersection;
	double				nearest_obj_distance;
	t_generic_object	*cur_obj;
	double				cur_obj_distance;
	double				t;

	obj_intersection.intersected = 0;
	nearest_obj_distance = DBL_MAX;
	cur_obj = objs;
	while (cur_obj)
	{
		cur_obj_distance = get_distance_through_ray(ray, cur_obj);
		if (cur_obj_distance < nearest_obj_distance)
			obj_intersection.intersected = cur_obj;
		if (cur_obj_distance < nearest_obj_distance)
			nearest_obj_distance = cur_obj_distance;
		cur_obj = cur_obj->next;
	}
	if (!obj_intersection.intersected)
		return (obj_intersection);
	t = get_intersecting_time_through_ray(ray, obj_intersection.intersected);
	obj_intersection.normal = get_fake_normal(obj_intersection.intersected, t);
	t = fabs(t);
	obj_intersection.intersection = get_point_through_ray_at_time(ray, t);
	return (obj_intersection);
}

static double	get_distance_through_ray(t_ray ray, t_generic_object *obj)
{
	double	t;

	t = get_intersecting_time_through_ray(ray, obj);
	return (calc_distance_from_ray_and_time(ray, t));
}

static double	get_intersecting_time_through_ray(t_ray ray,
					t_generic_object *obj)
{
	double	t;

	t = DBL_MAX;
	if (obj->type == SPHERE)
		t = get_intersecting_time_through_ray_with_sphere(ray,
				(t_sphere *) obj->specific_object);
	else if (obj->type == PLANE)
		t = get_intersecting_time_through_ray_with_plane(ray,
				(t_plane *) obj->specific_object);
	else if (obj->type == CYLINDER)
		t = get_intersecting_time_through_ray_with_cylinder(ray,
				(t_cylinder *) obj->specific_object);
	else if (obj->type == ELLIPSOID)
		t = get_intersecting_time_through_ray_with_ellipsoid(ray,
				(t_ellipsoid *) obj->specific_object);
	return (t);
}

static t_vector	get_fake_normal(t_generic_object *obj, double t)
{
	t_vector	normal;

	ft_bzero(&normal, sizeof(normal));
	if (t < 0)
	{
		normal = ((t_cylinder *) obj->specific_object)->orientation;
		if (((t_cylinder *) obj->specific_object)->last_cap_hitted)
			multiply_by_scalar(&normal, -1);
	}
	return (normal);
}
