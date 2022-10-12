/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_spherical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:39:22 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/12 14:58:20 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "geometric.h"

static double	get_inclination(t_point point);

t_spherical_point	to_spherical(t_point point)
{
	t_spherical_point	spherical;

	spherical.radius = vector_length(point);
	spherical.azimuth = acos(point.z / spherical.radius);
	spherical.inclination = get_inclination(point);
	return (spherical);
}

static double	get_inclination(t_point point)
{
	double	inclination;

	inclination = NAN;
	if (point.x > 0)
		inclination = atan(point.y / point.x);
	if (point.x < 0 && point.y >= 0)
		inclination = atan(point.y / point.x) + M_PI;
	if (point.x < 0 && point.y < 0)
		inclination = atan(point.y / point.x) - M_PI;
	if (point.x == 0 && point.y > 0)
		inclination = M_PI_2;
	if (point.x == 0 && point.y < 0)
		inclination = -M_PI_2;
	if (point.x == 0 && point.y == 0)
		inclination = 0;
	inclination += M_PI;
	return (inclination);
}
