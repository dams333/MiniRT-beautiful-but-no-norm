/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:23:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/30 12:21:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"

void	compute_specular_lightning_2(t_light_object *light, t_tables *tables,
	t_vector	reflected_directions, t_vector	eye_direction)
{
	float	specular_color[3];
	float	p;
	float	n;

	p = 0.5;
	n = 100;
	specular_color[0] = (1 - p) * tables->obj[0] + p;
	specular_color[1] = (1 - p) * tables->obj[1] + p;
	specular_color[2] = (1 - p) * tables->obj[2] + p;
	if (dot_product(reflected_directions, eye_direction) > 0)
	{
		tables->res[0] += light->brightness_ratio * (light->color_r / 255.0)
			* powf(dot_product(reflected_directions, eye_direction), n)
			* specular_color[0];
		tables->res[1] += light->brightness_ratio * (light->color_g / 255.0)
			* powf(dot_product(reflected_directions, eye_direction), n)
			* specular_color[1];
		tables->res[2] += light->brightness_ratio * (light->color_b / 255.0)
			* powf(dot_product(reflected_directions, eye_direction), n)
			* specular_color[2];
	}	
}

void	compute_specular_lightning(t_obj_intersection intersection,
	t_light_object *light, t_camera_object *camera,
	t_tables *tables)
{
	t_vector	reflected_directions;
	t_vector	light_direction;
	t_vector	eye_direction;
	t_vector	store;

	if (BONUS)
	{
		vector_substract(&light_direction, intersection.intersection,
			(t_point){light->coord_x, light->coord_y, light->coord_z});
		normalize(&light_direction);
		store = intersection.normal;
		multiply_by_scalar(&store,
			2 * dot_product(light_direction, intersection.normal));
		vector_substract(&reflected_directions, light_direction, store);
		normalize(&reflected_directions);
		vector_substract(&eye_direction, (t_point){camera->coord_x,
			camera->coord_y, camera->coord_z}, intersection.intersection);
		normalize(&eye_direction);
		compute_specular_lightning_2(light, tables, reflected_directions,
			eye_direction);
	}
}

bool	in_shadow(t_obj_intersection intersection,
	t_parsing *parsing, t_light_object *light)
{
	t_ray				ray;
	t_obj_intersection	shadow_intersect;

	ray.base = (t_point){light->coord_x, light->coord_y, light->coord_z};
	vector_substract(&(ray.vec), intersection.intersection, ray.base);
	shadow_intersect = get_intersecting_obj(ray, parsing->hittables);
	if (shadow_intersect.intersected != intersection.intersected)
		return (true);
	return (false);
}

void	compute_color(t_parsing *parsing, t_obj_intersection intersection,
	t_tables *tables, t_vector normal)
{
	t_generic_object	*light;

	tables->res[0] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_r / 255) * tables->obj[0];
	tables->res[1] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_g / 255) * tables->obj[1];
	tables->res[2] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_b / 255) * tables->obj[2];
	light = parsing->lights;
	while (light)
	{
		if (light->type == LIGHT)
		{
			if (!in_shadow(intersection, parsing, light->specific_object))
			{
				compute_diffuse_lightning(intersection, normal,
					(t_light_object *) light->specific_object, tables);
				compute_specular_lightning(intersection,
					(t_light_object *) light->specific_object, parsing->camera,
					tables);
			}
		}
		light = light->next;
	}
}

void	compute_pixel(t_params *params, t_obj_intersection i,
	int canvas_x, int canvas_y)
{
	t_vector	normal;
	t_tables	tables;

	if (i.intersected)
	{
		ft_bzero(tables.res, sizeof(*tables.res) * 3);
		get_obj_color(tables.obj, i.intersected, i.intersection,
			vector_length(i.normal) != 0);
		normal = compute_normal(i);
		perturb_normal(params, i, &normal, vector_length(i.normal));
		i.normal = normal;
		compute_color(params->parsing, i, &tables, normal);
		if (tables.res[0] > 1)
			tables.res[0] = 1;
		if (tables.res[1] > 1)
			tables.res[1] = 1;
		if (tables.res[2] > 1)
			tables.res[2] = 1;
		register_pixel(params->mlx, canvas_x, canvas_y, encode_rgb(tables.obj[0]
				* tables.res[0] * 255, tables.obj[1] * tables.res[1] * 255,
				tables.obj[2] * tables.res[2] * 255));
	}
	else
		register_pixel(params->mlx, canvas_x, canvas_y, encode_rgb(0, 0, 0));
}
