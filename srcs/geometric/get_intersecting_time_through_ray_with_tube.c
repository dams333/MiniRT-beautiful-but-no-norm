/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_time_through_ray_with_tube.c      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:25:41 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 21:18:59 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_intersecting_obj.h"
#include "get_nearest_positive_intersection.h"
#include "sec_degree_utils.h"

static t_vector	get_cylinder_axis_to_ray_base(t_point ray_base,
					t_cylinder *cylinder);
static t_vector	get_ray_base_to_cylinder(t_vector cylinder_orientation,
					t_vector ray_vec);
static int		is_in_cylinder(t_ray ray, t_cylinder *cylinder, double t);

double	get_intersecting_time_through_ray_with_tube(t_ray ray,
		t_cylinder *cylinder)
{
	t_vector				cylinder_axis_to_ray_base;
	t_sec_degree_factors	factors;
	t_vector				ray_base_to_cylinder;
	double					t;

	ray_base_to_cylinder = get_ray_base_to_cylinder(cylinder->orientation,
			ray.vec);
	cylinder_axis_to_ray_base = get_cylinder_axis_to_ray_base(ray.base,
			cylinder);
	factors.a = dot_product(ray_base_to_cylinder, ray_base_to_cylinder);
	factors.b = 2 * dot_product(cylinder_axis_to_ray_base,
			ray_base_to_cylinder);
	factors.c = dot_product(cylinder_axis_to_ray_base,
			cylinder_axis_to_ray_base) - pow(cylinder->diameter / 2, 2);
	t = get_nearest_positive_intersection(factors);
	if (isnan(t))
		return (NAN);
	if (!is_in_cylinder(ray, cylinder, t))
		return (NAN);
	return (t);
}

static t_vector	get_ray_base_to_cylinder(t_vector cylinder_orientation,
					t_vector ray_vec)
{
	t_vector	ray_base_to_cylinder;

	cross_product(&ray_base_to_cylinder, cylinder_orientation, ray_vec);
	cross_product(&ray_base_to_cylinder, ray_base_to_cylinder,
		cylinder_orientation);
	return (ray_base_to_cylinder);
}

static t_vector	get_cylinder_axis_to_ray_base(t_point ray_base,
					t_cylinder *cylinder)
{
	t_vector	cylinder_axis_to_ray_base;

	vector_substract(&cylinder_axis_to_ray_base, ray_base, cylinder->pos);
	cross_product(&cylinder_axis_to_ray_base, cylinder->orientation,
		cylinder_axis_to_ray_base);
	cross_product(&cylinder_axis_to_ray_base, cylinder_axis_to_ray_base,
		cylinder->orientation);
	return (cylinder_axis_to_ray_base);
}

static int	is_in_cylinder(t_ray ray, t_cylinder *cylinder, double t)
{
	t_vector	r_ray;
	t_vector	tmp_sub_r_ray;
	t_point		cylinder_top;

	r_ray = ray.vec;
	multiply_by_scalar(&r_ray, t);
	vector_add(&r_ray, r_ray, ray.base);
	vector_substract(&tmp_sub_r_ray, r_ray, cylinder->pos);
	if (dot_product(tmp_sub_r_ray, cylinder->orientation) < 0)
		return (0);
	cylinder_top = cylinder->orientation;
	multiply_by_scalar(&cylinder_top, cylinder->height);
	vector_add(&cylinder_top, cylinder_top, cylinder->pos);
	vector_substract(&tmp_sub_r_ray, r_ray, cylinder_top);
	if (dot_product(tmp_sub_r_ray, cylinder->orientation) > 0)
		return (0);
	return (1);
}
