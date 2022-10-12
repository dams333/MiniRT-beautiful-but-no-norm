/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cylindrical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:26:19 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/12 13:32:14 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "geometric.h"

t_cylindrical_point	to_cylindrical(t_point point)
{
	t_cylindrical_point	cy_point;
	t_spherical_point	sp_point;

	sp_point = to_spherical(point);
	cy_point.radius = sp_point.radius * sin(sp_point.inclination);
	cy_point.azimuth = sp_point.azimuth;
	cy_point.z = sp_point.radius * cos(sp_point.inclination);
	return (cy_point);
}
