/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:14:48 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 14:44:01 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

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
