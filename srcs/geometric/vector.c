/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:36:32 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/30 16:10:00 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"
#include <math.h>

void	from_point(t_vector *vector, t_point point1, t_point point2)
{
	vector->x = point2.x - point1.x;
	vector->y = point2.y - point1.y;
	vector->z = point2.z - point1.z;
}

double	vector_length(t_vector vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

void	normalize(t_vector *vector)
{
	double	length;

	length = vector_length(*vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

void	vector_add(t_vector *result, t_vector a, t_vector b)
{
	result->x = a.x + b.x;
	result->y = a.y + b.y;
	result->z = a.z + b.z;
}

void	vector_substract(t_vector *result, t_vector a, t_vector b)
{
	result->x = a.x - b.x;
	result->y = a.y - b.y;
	result->z = a.z - b.z;
}
