/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:46:54 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/17 13:19:17 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "geometric.h"
#include "get_intersecting_obj.h"

static double	get_distance_through_ray(t_ray ray, t_generic_object *obj);

t_generic_object	*get_intersecting_obj(t_ray ray, t_generic_object *objs)
{
	t_generic_object	*nearest_obj;
	double				nearest_obj_distance;
	t_generic_object	*cur_obj;
	double				cur_obj_distance;

	nearest_obj = 0;
	nearest_obj_distance = DBL_MAX;
	cur_obj = objs;
	while (cur_obj)
	{
		cur_obj_distance = get_distance_through_ray(ray, cur_obj);
		if (cur_obj_distance < nearest_obj_distance)
		{
			nearest_obj_distance = cur_obj_distance;
			nearest_obj = cur_obj;
		}
		cur_obj = cur_obj->next;
	}
	return (nearest_obj);
}

static double	get_distance_through_ray(t_ray ray, t_generic_object *obj)
{
	if (obj->type == SPHERE)
		return (get_distance_through_ray_with_sphere(ray,
			(t_sphere_object *) obj->specific_object));
	else if (obj->type == PLANE)
		return (get_distance_through_ray_with_plane(ray,
			(t_plane_object *) obj->specific_object));
	else if (obj->type == CYLINDER)
		return (get_distance_through_ray_with_cylinder(ray,
			(t_cylinder_object *) obj->specific_object));
	else
		return (DBL_MAX);
}
