/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:43:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/20 12:30:12 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "geometric_structs.h"
# include "sec_degree_factors.h"

typedef struct s_checkerboard
{
	int	height;
	int	width;
	int	color_r;
	int	color_g;
	int	color_b;
}	t_checkerboard;

typedef struct s_texture
{
	int		*data;
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef enum e_object_type
{
	CAMERA,
	AMBIENT_LIGHTNING,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	ELLIPSOID
}	t_object_type;

typedef struct s_generic_object
{
	t_object_type			type;
	void					*specific_object;
	struct s_generic_object	*next;
}	t_generic_object;

typedef struct s_texture_infos
{
	t_checkerboard	checkerboard;
	char			*texture_file;
	char			*normal_map_file;
}	t_texture_infos;

typedef struct s_ambient_lightning_object
{
	double	lightning_ratio;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_ambient_lightning_object;

typedef struct s_camera_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	orientation_x;
	double	orientation_y;
	double	orientation_z;
	int		horizontal_fov;
}	t_camera_object;

typedef struct s_light_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	brightness_ratio;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_light_object;

typedef struct s_sphere
{
	t_point			pos;
	double			diameter;
	int				color_r;
	int				color_g;
	int				color_b;
	t_texture_infos	texture_infos;
	t_texture		bump_map;
	t_texture		texture;
}	t_sphere;

typedef struct s_plane
{
	t_vector		orientation;
	double			d;
	int				color_r;
	int				color_g;
	int				color_b;
	t_texture_infos	texture_infos;
	t_texture		bump_map;
	t_texture		texture;
}	t_plane;

typedef struct s_cylinder
{
	t_point			pos;
	t_vector		orientation;
	double			diameter;
	double			height;
	int				color_r;
	int				color_g;
	int				color_b;
	t_texture_infos	texture_infos;
	t_texture		bump_map;
	t_texture		texture;
	int				last_cap_hitted;
}	t_cylinder;

typedef struct s_ellipsoid
{
	t_point					pos;
	t_sec_degree_factors	factors;
	int						color_r;
	int						color_g;
	int						color_b;
	t_texture_infos			texture_infos;
	t_texture				bump_map;
	t_texture				texture;
}	t_ellipsoid;

typedef struct s_parsing
{
	t_camera_object				*camera;
	t_ambient_lightning_object	*ambient_lightning;
	t_generic_object			*lights;
	t_generic_object			*hittables;
}	t_parsing;

typedef struct s_generic_object_metaed
{
	t_generic_object	*obj;
	int					is_cap;
}	t_generic_object_metaed;
#endif
