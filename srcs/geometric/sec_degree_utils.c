/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_degree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:51:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 11:23:57 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "distance_between_points.h"
#include "get_point_through_ray_at_time.h"
#include "sec_degree_utils.h"

double	calc_delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	get_first_root(double a, double b, double c)
{
	double	delta;

	delta = calc_delta(a, b, c);
	return ((-b - sqrt(delta)) / (2 * a));
}

double	get_second_root(double a, double b, double c)
{
	double	delta;

	delta = calc_delta(a, b, c);
	return ((-b + sqrt(delta)) / (2 * a));
}

double	calc_distance_from_ray_and_time(t_ray ray, double t)
{
	t_point	point;

	point = get_point_through_ray_at_time(ray, t);
	return (distance_between_points(point, ray.base));
}
