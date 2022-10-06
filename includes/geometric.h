/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/06 15:06:38 by dhubleur         ###   ########.fr       */
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

double		distance(t_point point1, t_point point2);

typedef t_point	t_vector;

typedef struct s_ray
{
	t_point	base;
	t_point	vec;
}	t_ray;

double		vector_length(t_vector vector);
void		normalize(t_vector *vector);
void		vector_add(t_vector *result, t_vector a, t_vector b);
void		vector_substract(t_vector *result, t_vector a, t_vector b);

void		multiply_by_scalar(t_vector *vec, double scalar);
void		divide_by_scalar(t_vector *vec, double scalar);
double		dot_product(t_vector v1, t_vector v2);

void		cross_product(t_vector *result, t_vector v1, t_vector v2);

typedef struct s_matrix3
{
	t_vector	a1;
	t_vector	a2;
	t_vector	a3;
}	t_matrix3;

t_matrix3	rotation_matrix_from_orientation(t_vector target);
t_point		matrix_mult_point(t_matrix3 matrix, t_point point);

float		degrees_to_radian(float degrees);

#endif
