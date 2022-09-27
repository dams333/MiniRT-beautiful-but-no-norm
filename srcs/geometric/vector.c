/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:36:32 by dhubleur          #+#    #+#             */
/*   Updated: 2022/06/27 14:41:23 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"
#include <math.h>

void    from_point(t_vector *vector, t_point point1, t_point point2)
{
    vector->x = point2.x - point1.x;
    vector->y = point2.y - point1.y;
    vector->z = point2.z - point1.z;
}

double vector_length(t_vector vector)
{
    return (pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

void normalize(t_vector *vector)
{
    double length;

    length = vector_length(*vector);
    vector->x /= length;
    vector->y /= length;
    vector->z /= length;
}

void vector_add(t_vector *vector, t_vector vector_add)
{
    vector->x += vector_add.x;
    vector->y += vector_add.y;
    vector->z += vector_add.z;
}

void vector_substract(t_vector *vector, t_vector vector_substract)
{
    vector->x -= vector_substract.x;
    vector->y -= vector_substract.y;
    vector->z -= vector_substract.z;
}

void multiply_by_scalar(t_vector *vector, double scalar)
{
    vector->x *= scalar;
    vector->y *= scalar;
    vector->z *= scalar;
}

void divide_by_scalar(t_vector *vector, double scalar)
{
    vector->x /= scalar;
    vector->y /= scalar;
    vector->z /= scalar;
}