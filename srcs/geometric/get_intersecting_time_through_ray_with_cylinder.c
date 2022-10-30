/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_time_through_ray_with_cylind      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:30:36 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/30 18:34:02 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "distance_between_points.h"
#include "geometric.h"
#include "get_intersecting_obj.h"
#include "get_point_through_ray_at_time.h"

static void		get_intersecting_time_through_ray_with_caps(t_ray ray,
					double distance_caps[2], t_cylinder *cylinder);
static double	get_intersecting_time_through_ray_with_cap(t_ray ray,
					t_cylinder *cylinder, t_point cap_center);
static double	abs_min_or_not_nan(double a, double b);

double	get_intersecting_time_through_ray_with_cylinder(t_ray ray,
			t_cylinder *cylinder)
{
	double	t_tube;
	double	t_caps[2];

	t_tube = get_intersecting_time_through_ray_with_tube(ray, cylinder);
	get_intersecting_time_through_ray_with_caps(ray, t_caps, cylinder);
	return (abs_min_or_not_nan(t_tube,
			abs_min_or_not_nan(t_caps[0], t_caps[1])));
}

static double	abs_min_or_not_nan(double a, double b)
{
	if (isnan(a))
		return (b);
	if (isnan(b))
		return (a);
	if (fabs(a) < fabs(b))
		return (a);
	return (b);
}

static void	get_intersecting_time_through_ray_with_caps(t_ray ray,
			double t_caps[2], t_cylinder *cylinder)
{
	t_point	cap_center;

	cap_center = cylinder->pos;
	t_caps[0] = -get_intersecting_time_through_ray_with_cap(ray,
			cylinder, cap_center);
	cap_center = cylinder->orientation;
	multiply_by_scalar(&cap_center, cylinder->height);
	vector_add(&cap_center, cap_center, cylinder->pos);
	t_caps[1] = -get_intersecting_time_through_ray_with_cap(ray, cylinder,
			cap_center);
	cylinder->last_cap_hitted = (isnan(t_caps[0]) || t_caps[1] > t_caps[0]);
}

static double	get_intersecting_time_through_ray_with_cap(t_ray ray,
				t_cylinder *cylinder, t_point cap_center)
{
	t_plane	cap_plane;
	t_point	intersection;
	double	t;
	double	r;

	cap_plane.orientation = cylinder->orientation;
	cap_plane.d = -cap_plane.orientation.x * cap_center.x
		- cap_plane.orientation.y * cap_center.y
		- cap_plane.orientation.z * cap_center.z;
	t = get_intersecting_time_through_ray_with_plane(ray, &cap_plane);
	intersection = get_point_through_ray_at_time(ray, t);
	r = cylinder->diameter / 2;
	if (distance_between_points(cap_center, intersection) <= r)
		return (t);
	return (NAN);
}
