/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 10:38:48 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRIC_H
# define GEOMETRIC_H

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

double				distance(t_point point1, t_point point2);

typedef t_point	t_vector;

typedef struct s_ray
{
	t_point	base;
	t_point	vec;
}	t_ray;

typedef struct s_spherical_point
{
	double	radius;
	double	azimuth;
	double	inclination;
}	t_spherical_point;

double				vector_length(t_vector vector);
void				normalize(t_vector *vector);
void				vector_add(t_vector *result, t_vector a, t_vector b);
void				vector_substract(t_vector *result, t_vector a, t_vector b);

void				multiply_by_scalar(t_vector *vec, double scalar);
void				divide_by_scalar(t_vector *vec, double scalar);
double				dot_product(t_vector v1, t_vector v2);

void				cross_product(t_vector *result, t_vector v1, t_vector v2);

t_spherical_point	to_spherical(t_point point);

#endif
