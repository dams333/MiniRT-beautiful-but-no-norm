/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:14:48 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 16:43:27 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_rotation_angles.h"
#include "rotate.h"

void	rotate_around_x(t_vector *vec, double angle)
{
	t_vector	result;

	result.x = vec->x;
	result.y = vec->y * cos(angle) - vec->z * sin(angle);
	result.z = vec->y * sin(angle) + vec->z * cos(angle);
	*vec = result;
}

void	rotate_around_y(t_vector *vec, double angle)
{
	t_vector	result;

	result.x = vec->x * cos(angle) + vec->z * sin(angle);
	result.y = vec->y;
	result.z = -vec->x * sin(angle) + vec->z * cos(angle);
	*vec = result;
}

void	rotate_around_z(t_vector *vec, double angle)
{
	t_vector	result;

	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = vec->x * sin(angle) + vec->y * cos(angle);
	result.z = vec->z;
	*vec = result;
}

t_point	rotate_to_z_axis(t_point point, t_vector orientation)
{
	double				x_angle;
	double				y_angle;
	t_vector			z;

	z.x = 0;
	z.y = 0;
	z.z = 1;
	x_angle = get_x_rotation_angle(orientation, z);
	rotate_around_x(&point, x_angle);
	rotate_around_x(&orientation, x_angle);
	y_angle = get_y_rotation_angle(orientation, z);
	rotate_around_y(&point, y_angle);
	return (point);
}
