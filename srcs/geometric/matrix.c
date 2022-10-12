/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:49:49 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/12 16:13:29 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometric.h"

t_point	matrix_mult(t_matrix3 matrix, t_point point)
{
	t_point	result;

	result.x = matrix.a1.x * point.x + matrix.a2.x * point.y + matrix.a3.x
		* point.z;
	result.y = matrix.a1.y * point.x + matrix.a2.y * point.y + matrix.a3.y
		* point.z;
	result.z = matrix.a1.z * point.x + matrix.a2.z * point.y + matrix.a3.z
		* point.z;
	return (result);
}

t_matrix3	rotation_matrix_from_orientation(t_vector target)
{
	t_vector	base;
	t_vector	axis;
	t_matrix3	result;
	double		angle;

	base = (t_vector){0, 0, 1};
	cross_product(&axis, base, target);
	angle = acos(dot_product(base, target));
	result.a1.x = cos(angle) + pow(axis.x, 2) * (1 - cos(angle));
	result.a1.y = axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle);
	result.a1.z = axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle);
	result.a2.x = axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle);
	result.a2.y = cos(angle) + pow(axis.y, 2) * (1 - cos(angle));
	result.a2.z = axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle);
	result.a3.x = axis.x * axis.z * (1 - cos(angle)) - axis.y * sin(angle);
	result.a3.y = axis.y * axis.z * (1 - cos(angle)) + axis.x * sin(angle);
	result.a3.z = cos(angle) + pow(axis.z, 2) * (1 - cos(angle));
	return (result);
}
