/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotation_angles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:31:39 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 14:41:27 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_rotation_angles.h"

double	get_x_rotation_angle(t_vector from, t_vector to)
{
	double	angle;

	angle = atan2(to.z, to.y) - atan2(from.z, from.y);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	get_y_rotation_angle(t_vector from, t_vector to)
{
	double	angle;

	angle = atan2(to.x, to.z) - atan2(from.x, from.z);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	get_z_rotation_angle(t_vector from, t_vector to)
{
	double	angle;

	angle = atan2(to.y, to.x) - atan2(from.y, from.x);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
