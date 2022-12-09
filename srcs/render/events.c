/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/12/09 14:54:39 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static int on_key_press(int keycode, void *param)
{
	t_params *params;

	params = (t_params *)param;
	if (keycode == XK_Escape)
		mlx_loop_end(params->mlx->mlx);
	else if (keycode != 65293)
	{
		key_pressed(keycode, params);
		render_image(params);
	}
	return (0);
}

static int on_close_window(void *param)
{
	t_xvar *xvar;

	xvar = (t_xvar *)param;
	mlx_loop_end(xvar);
	return (0);
}

static int on_mouse_press(int code, int x, int y, void *param)
{
	t_params *params;

	params = (t_params *)param;
	if (code == 1)
		click_on_screen(x, y, params);
	return (0);
}

static void update_objects(t_params *params, int change)
{
	t_generic_object *obj;

	obj = params->parsing->hittables;
	while (obj)
	{
		t_point *pos;
		t_point *increment;
		int *direction;
		if (obj->type == SPHERE)
		{
			pos = &((t_sphere *)obj->specific_object)->pos;
			increment = &((t_sphere *)obj->specific_object)->coord_increment;
			direction = &((t_sphere *)obj->specific_object)->direction;
		}
		else if (obj->type == CYLINDER)
		{
			pos = &((t_cylinder *)obj->specific_object)->pos;
			increment = &((t_cylinder *)obj->specific_object)->coord_increment;
			direction = &((t_cylinder *)obj->specific_object)->direction;
		}
		else if (obj->type == ELLIPSOID)
		{
			pos = &((t_ellipsoid *)obj->specific_object)->pos;
			increment = &((t_ellipsoid *)obj->specific_object)->coord_increment;
			direction = &((t_ellipsoid *)obj->specific_object)->direction;
		}
		if (*direction == 1)
		{
			pos->x += increment->x;
			pos->y += increment->y;
			pos->z += increment->z;
		}
		else
		{
			pos->x -= increment->x;
			pos->y -= increment->y;
			pos->z -= increment->z;
		}
		if (change)
		{
			*direction = !*direction;
		}
		obj = obj->next;
	}
}

static int loop_hook(void *param)
{
	t_params *params;
	static int frame = 0;
	static int update = 0;

	params = (t_params *)param;
	if (frame++ == 10 && params->second_map)
	{
		update++;
		update_objects(params, update == ANIM_UPDATE);
		render_image(params);
		frame = 0;
	}
	if (update == ANIM_UPDATE)
		update = 0;
	return (0);
}

void init_events(t_params *params)
{
	mlx_hook(params->mlx->win, 33, 1L << 17,
			 &on_close_window, params->mlx->mlx);
	mlx_key_hook(params->mlx->win, &on_key_press, params);
	mlx_mouse_hook(params->mlx->win, &on_mouse_press, params);
	mlx_loop_hook(params->mlx->mlx, &loop_hook, params);
}
