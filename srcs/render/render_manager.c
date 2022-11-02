/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/02 14:29:52 by jmaia            ###   ###               */
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

	x -= WINDOW_WIDTH / 2;
	y -= WINDOW_HEIGHT / 2;
	p = (t_point){x * render_infos.vw / WINDOW_WIDTH, y
		* render_infos.vh / WINDOW_HEIGHT, render_infos.distance};
	return (p);
}

void	render_image(t_params *params)
{
	t_render_infos		render_infos;
	int					canvas_x;
	int					canvas_y;
	t_ray				ray;
	t_obj_intersection	intersect;

	init_render(&render_infos, params);
	canvas_x = -1;
	canvas_y = -1;
	while (++canvas_x <= WINDOW_WIDTH)
	{
		while (++canvas_y <= WINDOW_HEIGHT)
		{
			ray.base = render_infos.origin;
			ray.vec = matrix_mult(render_infos.rotation_matrix,
					canvas_to_viewport(canvas_x, canvas_y, render_infos));
			normalize(&(ray.vec));
			intersect = get_intersecting_obj(ray, params->parsing->hittables);
			compute_pixel(params, intersect, canvas_x, canvas_y);
		}
		canvas_y = -1;
	}
	put_image(params->mlx);
}
