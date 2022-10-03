/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:43:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/03 14:29:50 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "geometric.h"
# include "sec_degree_factors.h"

typedef enum e_object_type
{
	CAMERA,
	AMBIENT_LIGHTNING,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_generic_object
{
	t_object_type			type;
	void					*specific_object;
	struct s_generic_object	*next;
}	t_generic_object;

typedef struct s_ambient_lightning_object
{
	float	lightning_ratio;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_ambient_lightning_object;

typedef struct s_camera_object
{
	float	coord_x;
	float	coord_y;
	float	coord_z;
	float	orientation_x;
	float	orientation_y;
	float	orientation_z;
	int		horizontal_fov;
}	t_camera_object;

typedef struct s_light_object
{
	float	coord_x;
	float	coord_y;
	float	coord_z;
	float	brightness_ratio;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_light_object;

typedef struct s_sphere_object
{
	float	coord_x;
	float	coord_y;
	float	coord_z;
	float	diameter;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_sphere_object;

typedef struct s_sphere
{
	t_point	pos;
	double	diameter;
	int		color;
}	t_sphere;

typedef struct s_plane_object
{
	float	coord_x;
	float	coord_y;
	float	coord_z;
	float	d;
	float	orientation_x;
	float	orientation_y;
	float	orientation_z;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_plane_object;

typedef struct s_plane
{
	t_vector	orientation;
	double		d;
	int			color;
}	t_plane;

typedef struct s_cylinder_object
{
	float	coord_x;
	float	coord_y;
	float	coord_z;
	float	orientation_x;
	float	orientation_y;
	float	orientation_z;
	float	diameter;
	float	height;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_cylinder_object;

typedef struct s_cylinder
{
	t_point		pos;
	t_vector	orientation;
	double		diameter;
	double		height;
	int			color;
}	t_cylinder;

typedef struct s_ellipsoid
{
	t_point					pos;
	t_sec_degree_factors	factors;
	int						color;
}	t_ellipsoid;

typedef struct s_parsing
{
	t_camera_object				*camera;
	t_ambient_lightning_object	*ambient_lightning;
	t_generic_object			*lights;
	t_generic_object			*hittables;
}	t_parsing;

#endif
