/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_degree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:51:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/01 14:44:09 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sec_degree_utils.h"
#include <math.h>

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
	t_point	intersection;

	intersection.x = ray.vec.x * t + ray.base.x;
	intersection.y = ray.vec.y * t + ray.base.y;
	intersection.z = ray.vec.z * t + ray.base.z;
	return (sqrt(pow(intersection.x - ray.base.x, 2)
			+ pow(intersection.y - ray.base.y, 2)
			+ pow(intersection.z - ray.base.z, 2)));
}
