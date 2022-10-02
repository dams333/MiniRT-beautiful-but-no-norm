/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersecting_obj.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:44:25 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 21:01:04 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INTERSECTING_OBJ_H
# define GET_INTERSECTING_OBJ_H

# include "geometric.h"
# include "structures.h"

double				get_intersecting_time_through_ray_with_cylinder(t_ray ray,
						t_cylinder *cylinder);
double				get_intersecting_time_through_ray_with_plane(t_ray ray,
						t_plane *plane);
double				get_intersecting_time_through_ray_with_sphere(t_ray ray,
						t_sphere *sphere);
double				get_intersecting_time_through_ray_with_tube(t_ray ray,
						t_cylinder *cylinder);
t_generic_object	*get_intersecting_obj(t_ray ray, t_generic_object *objs);

#endif
