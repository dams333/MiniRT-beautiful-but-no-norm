/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:28:58 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/02 14:26:35 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRIC_STRUCTS_H
# define GEOMETRIC_STRUCTS_H

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef t_point	t_vector;

typedef struct s_ray
{
	t_point	base;
	t_point	vec;
}	t_ray;

typedef struct s_matrix3
{
	t_vector	a1;
	t_vector	a2;
	t_vector	a3;
}	t_matrix3;

typedef struct s_spherical_point
{
	double	radius;
	double	azimuth;
	double	inclination;
}	t_spherical_point;

typedef struct s_cylindrical_point
{
	double	radius;
	double	azimuth;
	double	z;
}	t_cylindrical_point;

typedef struct s_ellipsoidal_point
{
	double	longitude;
	double	lattitude;
	double	height;
}	t_ellipsoidal_point;

typedef struct s_point2d
{
	double	x;
	double	y;
}	t_point2d;

#endif
