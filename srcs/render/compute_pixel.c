/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:23:24 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 13:35:42 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	compute_specular_lightning_2(t_light_object *light, float obj[3],
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
	res[0] += light->brightness_ratio * (light->color_r / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[0];
	res[1] += light->brightness_ratio * (light->color_g / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[1];
	res[2] += light->brightness_ratio * (light->color_b / 255)
		* powf(dot_product(reflected_directions, eye_direction), n)
		* specular_color[2];
}

void	compute_specular_lightning(t_obj_intersection intersection,
	t_vector normal, t_light_object *light, t_camera_object *camera,
	float obj[3], float res[3])
{
	t_vector	reflected_directions;
	t_vector	light_direction;
	t_vector	eye_direction;

	vector_substract(&light_direction, (t_point){light->coord_x, light->coord_y,
		light->coord_z}, intersection.intersection);
	normalize(&light_direction);
	multiply_by_scalar(&normal, 2 * dot_product(light_direction, normal));
	vector_add(&reflected_directions, light_direction, normal);
	normalize(&reflected_directions);
	vector_substract(&eye_direction, (t_point){camera->coord_x,
		camera->coord_y, camera->coord_z}, intersection.intersection);
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
					(t_light_object *) light->specific_object, obj, res);
				compute_specular_lightning(intersection, normal,
					(t_light_object *) light->specific_object, parsing->camera,
					obj, res);
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
	float		color[3];
	float		obj[3];
	t_vector	normal;

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	get_obj_color(color, intersection.intersected);
	normal = compute_normal(intersection);
	compute_color(params->parsing, intersection, obj, color, normal);
	my_pixel_put(params->mlx, canvas_x, canvas_y, encode_rgb(obj[0] * color[0], obj[1] * color[1], obj[2] * color[2]), false);
}
