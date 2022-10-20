/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/20 14:01:49 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRIC_H
# define GEOMETRIC_H

# include "structures.h"
# include "geometric_structs.h"

double				distance(t_point point1, t_point point2);
t_matrix3			rotation_matrix_from_orientation(t_vector target);
t_point				matrix_mult(t_matrix3 matrix, t_point point);
float				degrees_to_radian(float degrees);

double				vector_length(t_vector vector);
void				normalize(t_vector *vector);
void				vector_add(t_vector *result, t_vector a, t_vector b);
void				vector_substract(t_vector *result, t_vector a, t_vector b);

void				multiply_by_scalar(t_vector *vec, double scalar);
void				divide_by_scalar(t_vector *vec, double scalar);
double				dot_product(t_vector v1, t_vector v2);

void				cross_product(t_vector *result, t_vector v1, t_vector v2);

t_spherical_point	to_spherical(t_point point);
t_cylindrical_point	to_cylindrical(t_point base, t_vector orientation,
						double radius, t_point point);
t_ellipsoidal_point	to_ellipsoidal(t_ellipsoid ellispoid, t_point point);

#endif
