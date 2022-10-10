/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:23:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 14:06:48 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	compute_specular_lightning_2(t_light_object *light, t_tables tables,
	t_vector	reflected_directions, t_vector	eye_direction)
{
	float	specular_color[3];
	float	p;
	float	n;

	p = 0.5;
	n = 400;
	specular_color[0] = (1 - p) * tables.obj[0] + p;
	specular_color[1] = (1 - p) * tables.obj[1] + p;
	specular_color[2] = (1 - p) * tables.obj[2] + p;
	tables.res[0] += light->brightness_ratio * (light->color_r / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[0];
	tables.res[1] += light->brightness_ratio * (light->color_g / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[1];
	tables.res[2] += light->brightness_ratio * (light->color_b / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[2];
}

void	compute_specular_lightning(t_obj_intersection intersection,
	t_light_object *light, t_camera_object *camera,
	t_tables tables)
{
	t_vector	reflected_directions;
	t_vector	light_direction;
	t_vector	eye_direction;

	vector_substract(&light_direction, (t_point){light->coord_x, light->coord_y,
		light->coord_z}, intersection.intersection);
	normalize(&light_direction);
	multiply_by_scalar(&(intersection.normal),
		2 * dot_product(light_direction, intersection.normal));
	vector_add(&reflected_directions, light_direction, intersection.normal);
	normalize(&reflected_directions);
	vector_substract(&eye_direction, (t_point){camera->coord_x,
		camera->coord_y, camera->coord_z}, intersection.intersection);
	normalize(&eye_direction);
	compute_specular_lightning_2(light, tables, reflected_directions,
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
	t_tables tables, t_vector normal)
{
	t_generic_object	*light;

	tables.res[0] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_r / 255) * tables.obj[0];
	tables.res[1] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_g / 255) * tables.obj[1];
	tables.res[2] += parsing->ambient_lightning->lightning_ratio
		* (parsing->ambient_lightning->color_b / 255) * tables.obj[2];
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

static int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}
static void my_pixel_put(t_mlx *mlx_object, int x, int y, int color, bool put)
{
	int useless;

	static void *img = NULL;
	static int *data = NULL;
	if(!img || !data)
	{
		img = mlx_new_image(mlx_object->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		data = (int *)mlx_get_data_addr(img, &useless, &useless, &useless);
	}
	if(put)
	{
		mlx_put_image_to_window(mlx_object->mlx, mlx_object->win, img, 0, 0);
		mlx_destroy_image(mlx_object->mlx, img);
		img = NULL;
		data = NULL;
		return ;
	}
	if(x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	data[y * WINDOW_WIDTH + x] = color;
}

void	compute_pixel(t_params *params, t_obj_intersection intersection,
	int canvas_x, int canvas_y)
{
	t_vector	normal;
	t_tables	tables;

	tables.res[0] = 0;
	tables.res[1] = 0;
	tables.res[2] = 0;
	get_obj_color(tables.obj, intersection.intersected);
	normal = compute_normal(intersection);
	intersection.normal = normal;
	compute_color(params->parsing, intersection, tables, normal);
	my_pixel_put(params->mlx, canvas_x, canvas_y, encode_rgb(tables.obj[0] * tables.res[0], tables.obj[1] * tables.res[1], tables.obj[2] * tables.res[2]), false);
}
