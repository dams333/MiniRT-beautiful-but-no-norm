/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/06 15:49:23 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	init_render(t_render_infos *render_infos, t_params *params)
{
	t_vector	camera_orientation;

	render_infos->origin = (t_point){params->parsing->camera->coord_x,
		params->parsing->camera->coord_y, params->parsing->camera->coord_z};
	render_infos->vw = 1;
	render_infos->vh = WINDOW_HEIGHT / (float)WINDOW_WIDTH * render_infos->vw;
	render_infos->distance = (render_infos->vw / 2.0)
		/ tan(degrees_to_radian(params->parsing->camera->horizontal_fov / 2.0));
	camera_orientation = (t_vector){params->parsing->camera->orientation_x,
		params->parsing->camera->orientation_y,
		params->parsing->camera->orientation_z};
	normalize(&camera_orientation);
	render_infos->rotation_matrix
		= rotation_matrix_from_orientation(camera_orientation);
}

t_point	canvas_to_viewport(float x, float y, t_render_infos	render_infos)
{
	t_point	p;

	p = (t_point){x * render_infos.vw / WINDOW_WIDTH, y
		* render_infos.vh / WINDOW_HEIGHT, render_infos.distance};
	return (p);
}

void my_pixel_put(t_mlx *mlx_object, int x, int y, int color, bool put)
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

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	render_image(t_params *params)
{
	t_render_infos		render_infos;
	int					canvas_x;
	int					canvas_y;
	t_ray				ray;
	t_generic_object	*intersect;

	init_render(&render_infos, params);
	canvas_x = -(WINDOW_WIDTH / 2) - 1;
	canvas_y = -(WINDOW_HEIGHT / 2) - 1;
	while (++canvas_x <= WINDOW_WIDTH / 2)
	{
		while (++canvas_y <= WINDOW_HEIGHT / 2)
		{
			ray.base = render_infos.origin;
			ray.vec = matrix_mult_point(render_infos.rotation_matrix,
					canvas_to_viewport(canvas_x, canvas_y, render_infos));
			normalize(&(ray.vec));
			intersect = get_intersecting_obj(ray, params->parsing->hittables);
			if (intersect != NULL)
			{
				printf("Hitted\n");
				t_sphere_object *sphere = intersect->specific_object;
				my_pixel_put(params->mlx, canvas_x + WINDOW_WIDTH/2, canvas_y + WINDOW_HEIGHT/2, encode_rgb(sphere->color_r, sphere->color_g, sphere->color_b), false);
			}
		}
		canvas_y = -(WINDOW_HEIGHT / 2) - 1;
	}
	my_pixel_put(params->mlx, 0, 0, 0, true);
	printf("End of render !\n");
}
