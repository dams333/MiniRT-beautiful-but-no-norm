/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:41:53 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 13:57:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "render.h"

void	extract_coord(t_params *params, double *coords[3])
{
	t_point	*point;

	if (params->selected == NULL)
	{
		coords[0] = &(params->parsing->camera->coord_x);
		coords[1] = &(params->parsing->camera->coord_y);
		coords[2] = &(params->parsing->camera->coord_z);
	}
	else
	{
		if (params->selected->type == SPHERE)
			point = &(((t_sphere *)params->selected->specific_object)->pos);
		if (params->selected->type == CYLINDER)
			point = &(((t_cylinder *)params->selected->specific_object)->pos);
		//if (params->selected->type == PLANE)
		//	point = &(((t_plane *)params->selected->specific_object)->pos);
		coords[0] = &(point->x);
		coords[1] = &(point->y);
		coords[2] = &(point->z);
	}
}

void	move(int keycode, t_params *params)
{
	t_vector	ori;
	double		*coords[3];

	ori = (t_vector){params->parsing->camera->orientation_x,
		0, params->parsing->camera->orientation_z};
	normalize(&ori);
	extract_coord(params, coords);
	if (keycode == XK_w)
	{
		*(coords[0]) += ori.x * 0.1;
		*(coords[2]) += ori.z * 0.1;
	}
	else if (keycode == XK_s)
	{
		*(coords[0]) -= ori.x * 0.1;
		*(coords[2]) -= ori.z * 0.1;
	}
	else if (keycode == XK_d)
	{
		*(coords[0]) += ori.z * 0.1;
		*(coords[2]) += ori.x * 0.1;
	}
	else if (keycode == XK_a)
	{
		*(coords[0]) -= ori.z * 0.1;
		*(coords[2]) -= ori.x * 0.1;
	}
	else if (keycode == XK_space)
		*(coords[1]) -= 0.1;
	else if (keycode == XK_Shift_L)
		*(coords[1]) += 0.1;
}
