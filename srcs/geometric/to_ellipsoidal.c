/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_ellipsoidal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:32:23 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/20 14:00:05 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometric.h"
#include "structures.h"

static void	compute_height_and_lattitude(t_point point, t_ellipsoid ellipsoid, double *height, double *lat);

t_ellipsoidal_point	to_ellipsoidal(t_ellipsoid ellipsoid, t_point point)
{
	t_ellipsoidal_point	el_point;

	vector_substract(&point, point, ellipsoid.pos);
	el_point.longitude = atan2(point.y, point.x) + M_PI;
	compute_height_and_lattitude(point, ellipsoid, &el_point.height, &el_point.lattitude);
	el_point.lattitude += M_PI;
	return (el_point);
}

void	compute_height_and_lattitude(t_point point, t_ellipsoid ellipsoid, double *height, double *lat)
{
	double	e_2;
	double	p;
	double	f;
	double	n;

	f = 1 - ellipsoid.factors.b / ellipsoid.factors.a;
	e_2 = 2 * f - pow(f, 2);
	p = sqrt(pow(point.x, 2) + pow(point.y, 2));
	*lat = atan2(point.z, ((1 - e_2) * p));
	for (int i = 0; i < 10; i++)
	{
		n = ellipsoid.factors.a / sqrt(1 - e_2 * pow(sin(*lat), 2));
		*height = p / cos(*lat) - n;
		*lat = atan2(point.z, ((1 - e_2 * n / (n + *height)) * p));
	}
}
