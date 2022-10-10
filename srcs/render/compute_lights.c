/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:26:51 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 13:37:30 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_obj_color(float color[3], t_generic_object *intersected)
{
	if (intersected->type == SPHERE)
	{
		color[0] = ((t_sphere_object *) intersected->specific_object)->color_r;
		color[1] = ((t_sphere_object *) intersected->specific_object)->color_g;
		color[2] = ((t_sphere_object *) intersected->specific_object)->color_b;
	}
	if (intersected->type == CYLINDER)
	{
		color[0] = ((t_cylinder_object *) intersected->specific_object)->color_r;
		color[1] = ((t_cylinder_object *) intersected->specific_object)->color_g;
		color[2] = ((t_cylinder_object *) intersected->specific_object)->color_b;
	}
	if (intersected->type == PLANE)
	{
		color[0] = ((t_plane_object *) intersected->specific_object)->color_r;
		color[1] = ((t_plane_object *) intersected->specific_object)->color_g;
		color[2] = ((t_plane_object *) intersected->specific_object)->color_b;
	}
	color[0] /= 255;
	color[1] /= 255;
	color[2] /= 255;
}

t_vector	compute_normal(t_obj_intersection intersection)
{
	t_sphere_object	*sphere;
	t_vector		normal;

	if (intersection.intersected->type == SPHERE)
	{
		sphere = intersection.intersected->specific_object;
		vector_substract(&normal, intersection.intersection,
			(t_point){sphere->coord_x, sphere->coord_y, sphere->coord_z});
	}
	normalize(&normal);
	return (normal);
}

void	compute_diffuse_lightning(t_obj_intersection intersection,
	t_vector normal, t_light_object *light, float obj[3], float res[3])
{
	float		n_dot_l;
	t_vector	light_direction;

	vector_substract(&light_direction, (t_point){light->coord_x, light->coord_y,
		light->coord_z}, intersection.intersection);
	normalize(&light_direction);
	normalize(&normal);
	n_dot_l = dot_product(normal, light_direction);
	if (n_dot_l > 0)
	{
		res[0] += light->brightness_ratio * (light->color_r / 255)
			* n_dot_l * obj[0];
		res[1] += light->brightness_ratio * (light->color_g / 255)
			* n_dot_l * obj[1];
		res[2] += light->brightness_ratio * (light->color_b / 255)
			* n_dot_l * obj[2];
	}
}
