/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_time_through_ray_with_plane.      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:25:21 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/11 16:06:48 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_intersecting_obj.h"
#include "sec_degree_utils.h"

static double	get_numerator(t_ray ray, t_plane *plane);
static double	get_denominator(t_ray ray, t_plane *plane);

double	get_intersecting_time_through_ray_with_plane(t_ray ray, t_plane *plane)
{
	double	numerator;
	double	denominator;
	double	t;

	numerator = get_numerator(ray, plane);
	denominator = get_denominator(ray, plane);
	if (numerator == 0 && denominator == 0)
		return (0.0);
	if (denominator == 0)
		return (NAN);
	t = numerator / denominator;
	if (t < 0)
		return (NAN);
	return (t);
}

static double	get_numerator(t_ray ray, t_plane *plane)
{
	return (-plane->orientation.x * ray.base.x
		- plane->orientation.y * ray.base.y
		- plane->orientation.z * ray.base.z
		- plane->d);
}

static double	get_denominator(t_ray ray, t_plane *plane)
{
	return (plane->orientation.x * ray.vec.x
		+ plane->orientation.y * ray.vec.y
		+ plane->orientation.z * ray.vec.z);
}
