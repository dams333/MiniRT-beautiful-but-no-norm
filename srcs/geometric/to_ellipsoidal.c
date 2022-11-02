/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_ellipsoidal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:32:23 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/02 14:27:09 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometric.h"
#include "structures.h"

static void	compute_lattitude(t_point point, t_ellipsoid ellipsoid,
				double *lat);

t_ellipsoidal_point	to_ellipsoidal(t_ellipsoid ellipsoid, t_point point)
{
	t_ellipsoidal_point	el_point;

	vector_substract(&point, point, ellipsoid.pos);
	el_point.longitude = atan2(point.y, point.x) + M_PI;
	compute_lattitude(point, ellipsoid, &el_point.lattitude);
	el_point.lattitude += M_PI;
	return (el_point);
}

void	compute_lattitude(t_point point, t_ellipsoid ellipsoid,
			double *lat)
{
	double	e_2;
	double	p;
	double	f;
	double	v;
	double	last_lat;

	f = 1 - ellipsoid.factors.b / ellipsoid.factors.a;
	e_2 = 2 * f - pow(f, 2);
	p = sqrt(pow(point.x, 2) + pow(point.y, 2));
	*lat = atan(point.z / ((1 - e_2) * p));
	last_lat = NAN;
	while (!(fabs(last_lat - *lat) < 0.01))
	{
		last_lat = *lat;
		v = ellipsoid.factors.a / sqrt(1 - e_2 * pow(sin(*lat), 2));
		*lat = atan((point.z + e_2 * v * sin(*lat)) / p);
	}
}
