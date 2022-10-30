/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:26:51 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/30 12:09:02 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_obj_color(float c[3], t_generic_object *intersected,
	t_point intersection, int is_cap)
{
	if (intersected->type == SPHERE)
	{
		c[0] = ((t_sphere *)intersected->specific_object)->color_r / 255.0;
		c[1] = ((t_sphere *)intersected->specific_object)->color_g / 255.0;
		c[2] = ((t_sphere *)intersected->specific_object)->color_b / 255.0;
	}
	if (intersected->type == CYLINDER)
	{
		c[0] = ((t_cylinder *)intersected->specific_object)->color_r / 255.0;
		c[1] = ((t_cylinder *)intersected->specific_object)->color_g / 255.0;
		c[2] = ((t_cylinder *)intersected->specific_object)->color_b / 255.0;
	}
	if (intersected->type == PLANE)
	{
		c[0] = ((t_plane *)intersected->specific_object)->color_r / 255.0;
		c[1] = ((t_plane *)intersected->specific_object)->color_g / 255.0;
		c[2] = ((t_plane *)intersected->specific_object)->color_b / 255.0;
	}
	if (intersected->type == ELLIPSOID)
	{
		c[0] = ((t_ellipsoid *)intersected->specific_object)->color_r / 255.0;
		c[1] = ((t_ellipsoid *)intersected->specific_object)->color_g / 255.0;
		c[2] = ((t_ellipsoid *)intersected->specific_object)->color_b / 255.0;
	}
	load_texture_color(c, intersected, intersection, is_cap);
}

t_vector	compute_cylinder_body_normal(t_cylinder *cylinder,
	t_obj_intersection intersection)
{
	double		t;
	t_vector	vector;
	t_point		pt;
	t_vector	normal;

	vector_substract(&vector, intersection.intersection, cylinder->pos);
	t = dot_product(vector, cylinder->orientation);
	vector = cylinder->orientation;
	multiply_by_scalar(&vector, t);
	vector_add(&pt, cylinder->pos, vector);
	vector_substract(&(normal), intersection.intersection, pt);
	normal.x = -normal.x;
	normal.y = -normal.y;
	normal.z = -normal.z;
	return (normal);
}

t_vector	get_sp_pl_normal(t_obj_intersection intersection)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_vector	normal;

	if (intersection.intersected->type == SPHERE)
	{
		sphere = intersection.intersected->specific_object;
		vector_substract(&normal, sphere->pos, intersection.intersection);
	}
	else
	{
		plane = intersection.intersected->specific_object;
		normal = (t_vector){plane->orientation.x, plane->orientation.y,
			plane->orientation.z};
	}
	return (normal);
}

t_vector	compute_normal(t_obj_intersection intersection)
{
	t_ellipsoid	*ellipsoid;
	t_vector	normal;

	if (intersection.intersected->type == SPHERE)
		normal = get_sp_pl_normal(intersection);
	if (intersection.intersected->type == PLANE)
		normal = get_sp_pl_normal(intersection);
	if (intersection.intersected->type == CYLINDER)
	{
		if (vector_length(intersection.normal) != 0)
			normal = intersection.normal;
		else
			normal = compute_cylinder_body_normal(
					intersection.intersected->specific_object, intersection);
	}
	if (intersection.intersected->type == ELLIPSOID)
	{
		ellipsoid = intersection.intersected->specific_object;
		normal = (t_vector){-intersection.intersection.x
			/ pow(ellipsoid->factors.a, 2),
			-intersection.intersection.y / pow(ellipsoid->factors.b, 2),
			-intersection.intersection.z / pow(ellipsoid->factors.c, 2)};
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
	if (n_dot_l <= 0 && intersection.intersected->type == PLANE)
		n_dot_l = dot_product((t_vector)
			{-normal.x, -normal.y, -normal.z}, light_direction);
	if (n_dot_l > 0)
	{
		tables->res[0] += light->brightness_ratio * (light->color_r / 255.0)
			* n_dot_l * tables->obj[0];
		tables->res[1] += light->brightness_ratio * (light->color_g / 255.0)
			* n_dot_l * tables->obj[1];
		tables->res[2] += light->brightness_ratio * (light->color_b / 255.0)
			* n_dot_l * tables->obj[2];
	}
}
