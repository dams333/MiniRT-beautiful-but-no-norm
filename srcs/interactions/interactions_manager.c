/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:22:15 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/13 16:17:20 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "render.h"
#include "geometric.h"

static const char	g_object_type[7][99] = {
	"camera",
	"ambient_lightning",
	"light",
	"sphere",
	"plane",
	"cylinder",
	"ellipsoid"
};

void	click_on_screen(int x, int y, t_params *params)
{
	t_render_infos		render_infos;
	t_ray				ray;
	t_obj_intersection	intersect;

	init_render(&render_infos, params);
	ray.base = (t_point){params->parsing->camera->coord_x,
		params->parsing->camera->coord_y, params->parsing->camera->coord_z};
	ray.vec = matrix_mult(render_infos.rotation_matrix,
			canvas_to_viewport(x, y, render_infos));
	normalize(&(ray.vec));
	intersect = get_intersecting_obj(ray, params->parsing->hittables);
	if (intersect.intersected != NULL)
	{
		params->selected = intersect.intersected;
		printf("Selected object of type %s\n",
			g_object_type[intersect.intersected->type]);
	}
}

void	key_pressed(int keycode, t_params *params)
{
	if (keycode == XK_q)
	{
		printf("Unselected object\n");
		params->selected = NULL;
	}
	if (keycode == XK_w || keycode == XK_a || keycode == XK_s
		|| keycode == XK_d || keycode == XK_space || keycode == XK_Shift_L)
		move(keycode, params);
	if (keycode == XK_f || keycode == XK_g || keycode == XK_e
		|| keycode == XK_r)
		resize(keycode, params);
	if (keycode == XK_z || keycode == XK_x)
		view(keycode, params);
	if (keycode == XK_i || keycode == XK_j
		|| keycode == XK_k || keycode == XK_l)
		rotate(keycode, params);
}
