/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:46:54 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/04 13:22:09 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "geometric.h"
#include "get_intersecting_obj.h"
#include "get_point_through_ray_at_time.h"
#include "obj_intersection.h"
#include "sec_degree_utils.h"

static double	get_distance_through_ray(t_ray ray, t_generic_object *obj);
static double	get_intersecting_time_through_ray(t_ray ray,
					t_generic_object *obj);

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
		{
			nearest_obj_distance = cur_obj_distance;
			obj_intersection.intersected = cur_obj;
		}
		cur_obj = cur_obj->next;
	}
	t = get_intersecting_time_through_ray(ray, obj_intersection.intersected);
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
	return (t);
}
