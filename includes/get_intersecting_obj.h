/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_obj.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:44:25 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/17 13:19:14 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INTERSECTING_OBJ_H
# define GET_INTERSECTING_OBJ_H

# include "geometric.h"
# include "structures.h"

t_generic_object	*get_intersecting_obj(t_ray ray, t_generic_object *objs);
double				get_distance_through_ray_with_sphere(t_ray ray,
						t_sphere_object *sphere);
double				get_distance_through_ray_with_plane(t_ray ray,
						t_plane_object *plane);
double				get_distance_through_ray_with_cylinder(t_ray ray,
						t_cylinder_object *cylinder);

#endif
