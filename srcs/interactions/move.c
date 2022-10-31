/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:41:53 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/31 13:01:02 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "render.h"

void	extract_obj_coord(t_params *params, double *coords[3])
{
	t_point	*point;

	if (params->selected->type == SPHERE)
		point = &(((t_sphere *)params->selected->specific_object)->pos);
	if (params->selected->type == CYLINDER)
		point = &(((t_cylinder *)params->selected->specific_object)->pos);
	if (params->selected->type == ELLIPSOID)
		point = &(((t_ellipsoid *)params->selected->specific_object)->pos);
	if (params->selected->type == SPHERE || params->selected->type == CYLINDER
		|| params->selected->type == ELLIPSOID)
	{
		coords[0] = &(point->x);
		coords[1] = &(point->y);
		coords[2] = &(point->z);
	}
	else if (params->selected->type == PLANE)
	{
		coords[0] = &(((t_plane *)params->selected->specific_object)->d);
		coords[1] = &(((t_plane *)params->selected->specific_object)->d);
		coords[2] = &(((t_plane *)params->selected->specific_object)->d);
	}
}

void	extract_coord(t_params *params, double *coords[3])
{
	if (params->selected == NULL)
	{
		coords[0] = &(params->parsing->camera->coord_x);
		coords[1] = &(params->parsing->camera->coord_y);
		coords[2] = &(params->parsing->camera->coord_z);
	}
	else
		extract_obj_coord(params, coords);
}

void	exec_move(int keycode, double *coords[3])
{
	if (keycode == XK_w)
		*(coords[2]) += 0.1;
	else if (keycode == XK_s)
		*(coords[2]) -= 0.1;
	else if (keycode == XK_d)
		*(coords[0]) += 0.1;
	else if (keycode == XK_a)
		*(coords[0]) -= 0.1;
	else if (keycode == XK_space)
		*(coords[1]) -= 0.1;
	else if (keycode == XK_Shift_L)
		*(coords[1]) += 0.1;
}

void	move(int keycode, t_params *params)
{
	double		*coords[3];
	double		tmp;

	tmp = 0;
	coords[0] = &tmp;
	coords[1] = &tmp;
	coords[2] = &tmp;
	extract_coord(params, coords);
	exec_move(keycode, coords);
}
