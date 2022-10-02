/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point_through_ray_at_time.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:17:13 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 11:17:21 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_point_through_ray_at_time.h"

t_point	get_point_through_ray_at_time(t_ray ray, double t)
{
	t_point	point;

	point.x = ray.vec.x * t + ray.base.x;
	point.y = ray.vec.y * t + ray.base.y;
	point.z = ray.vec.z * t + ray.base.z;
	return (point);
}
