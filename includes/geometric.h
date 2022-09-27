/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/27 17:52:24 by jmaia            ###   ###               */
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

double	distance(t_point point1, t_point point2);

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}	t_vector;

typedef struct s_ray
{
	t_point	base;
	t_point	vec;
}	t_ray;

double	vector_length(t_vector vector);
void	normalize(t_vector *vector);
void	vector_add(t_vector *vector, t_vector vector_add);
void	vector_substract(t_vector *vector, t_vector vector_substract);
void	multiply_by_scalar(t_vector *vector, double scalar);
void	divide_by_scalar(t_vector *vector, double scalar);

#endif
