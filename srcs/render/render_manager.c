/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/06 15:12:19 by dhubleur         ###   ########.fr       */
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

void	render_image(t_params *params)
{
	t_render_infos	render_infos;

	init_render(&render_infos, params);
}
