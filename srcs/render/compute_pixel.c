/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:23:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 13:23:18 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_obj_color(float color[3], t_generic_object *intersected)
{
	if (intersected->type == SPHERE)
	{
		color[0] = ((t_sphere_object) intersected->specific_object)->color_r;
		color[1] = ((t_sphere_object) intersected->specific_object)->color_g;
		color[2] = ((t_sphere_object) intersected->specific_object)->color_b;
	}
	if (intersected->type == CYLINDER)
	{
		color[0] = ((t_cylinder_object) intersected->specific_object)->color_r;
		color[1] = ((t_cylinder_object) intersected->specific_object)->color_g;
		color[2] = ((t_cylinder_object) intersected->specific_object)->color_b;
	}
	if (intersected->type == PLANE)
	{
		color[0] = ((t_plane_object) intersected->specific_object)->color_r;
		color[1] = ((t_plane_object) intersected->specific_object)->color_g;
		color[2] = ((t_plane_object) intersected->specific_object)->color_b;
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
	t_vector normal, t_light_object light, float obj[3], float res[3])
{
	float		n_dot_l;
	t_vector	light_direction;

	light_direction = substract((t_point){light.coord_x, light.coord_y,
			light.coord_z}, point);
	light_direction = normalize(light_direction);
	normal = normalize(normal);
	n_dot_l = dot_product(normal, light_direction);
	if (n_dot_l > 0)
	{
		res[0] += light.brightness_ratio * (light.color_r / 255)
			* n_dot_l * obj[0];
		res[1] += light.brightness_ratio * (light.color_g / 255)
			* n_dot_l * obj[1];
		res[2] += light.brightness_ratio * (light.color_b / 255)
			* n_dot_l * obj[2];
	}
}

void	compute_specular_lightning_2(t_light_object light, float obj[3],
	float res[3], t_vector	reflected_directions, t_vector	eye_direction)
{
	float	specular_color[3];
	float	p;
	float	n;

	p = 0.5;
	n = 400;
	specular_color[0] = (1 - p) * obj[0] + p;
	specular_color[1] = (1 - p) * obj[1] + p;
	specular_color[2] = (1 - p) * obj[2] + p;
	res[0] += light.brightness_ratio * (light.color_r / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[0];
	res[1] += light.brightness_ratio * (light.color_g / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[1];
	res[2] += light.brightness_ratio * (light.color_b / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[2];
}

void	compute_specular_lightning(t_obj_intersection intersection,
	t_vector normal, t_light_object light, t_camera_object camera,
	float obj[3], float res[3])
{
	t_vector	reflected_directions;
	t_vector	light_direction;
	t_vector	eye_direction;

	vector_substract(&light_direction, (t_point){light.coord_x, light.coord_y,
		light.coord_z}, intersection.intersection);
	normalize(&light_direction);
	vector_add(&reflected_directions, light_direction,
		multiply_by_scalar(normal, 2 * dot_product(light_direction, normal)));
	normalize(&reflected_directions);
	vector_substract(&eye_direction, (t_point){camera.coord_x,
		camera.coord_y, camera.coord_z}, intersection.intersection);
	normalize(&eye_direction);
	compute_specular_lightning_2(light, obj, res, reflected_directions,
		eye_direction);
}

bool	in_shadow(t_obj_intersection intersection,
	t_parsing *parsing, t_light_object *light)
{
	t_ray				ray;
	t_obj_intersection	shadow_intersect;

	ray.base = intersection.intersection;
	vector_substract(&(ray.vec),
		(t_point){light->coord_x, light->coord_y, light->coord_z},
		intersection.intersection);
	shadow_intersect = get_intersecting_obj(ray, parsing->hittables);
	if (shadow_intersect.intersected)
	{
		if (distance(shadow_intersect.intersection, intersection.intersection)
			< distance((t_point){light->coord_x, light->coord_y,
				light->coord_z},
			intersection.intersection))
			return (true);
	}
	return (false);
}

void	compute_color(t_parsing *parsing, t_obj_intersection intersection,
	float obj[3], float res[3], t_vector normal)
{
	t_generic_object	*light;

	res[0] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_r / 255) * res[0];
	res[1] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_g / 255) * res[1];
	res[2] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_b / 255) * res[2];
	light = parsing->lights;
	while (light)
	{
		if (light->type == LIGHT)
		{
			if (!in_shadow(intersection, parsing, light->specific_object))
			{
				compute_diffuse_lightning(intersection, normal,
					light->specific_object, obj, res);
				compute_specular_lightning(intersection, normal,
					light->specific_object, parsing->camera, obj, res);
			}
		}
		light = light->next;
	}
}

void	compute_pixel(t_params *params, t_obj_intersection intersection,
	int canvas_x, int canvas_y)
{
	float	color[3];
	float	obj[3];
	t_ray	normal;

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	get_obj_color(color, intersection.intersected);
	normal = compute_normal(intersection);
	compute_color(params->parsing, intersection, obj, color, normal);
	my_pixel_put(params->mlx, canvas_x, canvas_y, color[0] << 16 | color[1] << 8 | color[2], false);
}
