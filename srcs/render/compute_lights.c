/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:26:51 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 15:16:08 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_obj_color(float color[3], t_generic_object *intersected)
{
	if (intersected->type == SPHERE)
	{
		color[0] = ((t_sphere *)intersected->specific_object)->color_r;
		color[1] = ((t_sphere *)intersected->specific_object)->color_g;
		color[2] = ((t_sphere *)intersected->specific_object)->color_b;
	}
	if (intersected->type == CYLINDER)
	{
		color[0] = ((t_cylinder *)intersected->specific_object)->color_r;
		color[1] = ((t_cylinder *)intersected->specific_object)->color_g;
		color[2] = ((t_cylinder *)intersected->specific_object)->color_b;
	}
	if (intersected->type == PLANE)
	{
		color[0] = ((t_plane *)intersected->specific_object)->color_r;
		color[1] = ((t_plane *)intersected->specific_object)->color_g;
		color[2] = ((t_plane *)intersected->specific_object)->color_b;
	}
	color[0] /= 255;
	color[1] /= 255;
	color[2] /= 255;
}

t_vector	compute_normal(t_obj_intersection intersection)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_vector	normal;

	if (intersection.intersected->type == SPHERE)
	{
		sphere = intersection.intersected->specific_object;
		vector_substract(&normal, sphere->pos, intersection.intersection);
	}
	if (intersection.intersected->type == PLANE)
	{
		plane = intersection.intersected->specific_object;
		normal = (t_vector){plane->orientation.x, plane->orientation.y,
			plane->orientation.z};
	}
	if (intersection.intersected->type == CYLINDER)
	{
		normal = (t_vector){intersection.intersection.x,
			intersection.intersection.y, 0};
	}
	normalize(&normal);
	return (normal);
}

void	compute_diffuse_lightning(t_obj_intersection intersection,
	t_vector normal, t_light_object *light, t_tables *tables)
{
	float		n_dot_l;
	t_vector	light_direction;

	vector_substract(&light_direction, intersection.intersection,
		(t_point){light->coord_x, light->coord_y, light->coord_z});
	normalize(&light_direction);
	n_dot_l = dot_product(normal, light_direction);
	if (n_dot_l > 0)
	{
		tables->res[0] += light->brightness_ratio * (light->color_r / 255)
			* n_dot_l * tables->obj[0];
		tables->res[1] += light->brightness_ratio * (light->color_g / 255)
			* n_dot_l * tables->obj[1];
		tables->res[2] += light->brightness_ratio * (light->color_b / 255)
			* n_dot_l * tables->obj[2];
	}
}
