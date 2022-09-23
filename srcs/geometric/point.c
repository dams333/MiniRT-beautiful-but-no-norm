/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:38:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/23 12:24:31 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"
#include <math.h>

double	distance(t_point point1, t_point point2)
{
	return (sqrt(pow(point1.x - point2.x, 2)
			+ pow(point1.y - point2.y, 2)
			+ pow(point1.z - point2.z, 2)));
}
