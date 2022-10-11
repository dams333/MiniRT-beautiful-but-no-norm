/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:41:53 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 14:49:21 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "render.h"

t_vector	*extract_vector(t_params *params)
{
	if (params->selected->type == PLANE)
		return (&((t_plane *)params->selected->specific_object)->orientation);
	if (params->selected->type == CYLINDER)
		return (&((t_cylinder *)
				params->selected->specific_object)->orientation);
	else
		return (NULL);
}

void	exec_vector_rotation(int keycode, t_vector *vector)
{
	t_vector	result;
	float		angle;

	angle = degrees_to_radian(2);
	if (keycode == XK_i || keycode == XK_j)
		angle = -angle;
	if (keycode == XK_j || keycode == XK_l)
	{
		result.x = vector->x * cos(angle) - vector->z * sin(angle);
		result.y = vector->y;
		result.z = -vector->x * sin(angle) + vector->z * cos(angle);
	}
	if (keycode == XK_i || keycode == XK_k)
	{
		result.x = vector->x;
		result.y = vector->y * cos(angle) - vector->z * sin(angle);
		result.z = vector->y * sin(angle) + vector->z * cos(angle);
	}
	normalize(&result);
	*vector = result;
}

void	exec_camera_rotation(int keycode, t_camera_object *camera)
{
	t_vector	vector;

	vector = (t_vector){camera->orientation_x,
		camera->orientation_y, camera->orientation_z};
	exec_vector_rotation(keycode, &vector);
	camera->orientation_x = vector.x;
	camera->orientation_y = vector.y;
	camera->orientation_z = vector.z;
}

void	rotate(int keycode, t_params *params)
{
	t_vector	*direction;

	if (params->selected == NULL)
		return (exec_camera_rotation(keycode, params->parsing->camera));
	else
		direction = extract_vector(params);
	if (direction)
		exec_vector_rotation(keycode, direction);
}
