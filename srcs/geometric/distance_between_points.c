/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_between_points.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:18:14 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 11:24:37 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "distance_between_points.h"

double	distance_between_points(t_point a, t_point b)
{
	return (sqrt(pow(b.x - a.x, 2)
			+ pow(b.y - a.y, 2)
			+ pow(b.z - a.z, 2)));
}
