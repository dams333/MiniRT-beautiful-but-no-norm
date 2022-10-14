/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:27 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/14 16:31:47 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <math.h>

# include "structures.h"
# include "window_props.h"
# include "geometric.h"
# include "get_intersecting_obj.h"
# include "render.h"

typedef struct s_render_infos
{
	t_point		origin;
	float		vw;
	float		vh;
	float		distance;
	t_matrix3	rotation_matrix;
}	t_render_infos;

typedef struct s_params
{
	t_parsing			*parsing;
	t_mlx				*mlx;
	t_generic_object	*selected;
}	t_params;

typedef struct s_tables
{
	float	res[3];
	float	obj[3];
}	t_tables;

void		render_image(t_params *params);
void		compute_pixel(t_params *params, t_obj_intersection intersection,
				int canvas_x, int canvas_y);
void		get_obj_color(float color[3], t_generic_object *intersected,
				t_point intersection);
t_vector	compute_normal(t_obj_intersection intersection);
void		compute_diffuse_lightning(t_obj_intersection intersection,
				t_vector normal, t_light_object *light,
				t_tables *tables);
int			encode_rgb(int red, int green, int blue);
void		register_pixel(t_mlx *mlx, int x, int y, int color);
void		put_image(t_mlx *mlx);
void		init_render(t_render_infos *render_infos, t_params *params);
t_point		canvas_to_viewport(float x, float y, t_render_infos	render_infos);
t_texture	load_map(t_mlx *mlx, char *file);
void		perturb_normal(t_params *params, t_obj_intersection intersection,
				t_vector *normal);
void		load_textures(t_mlx *mlx, t_parsing *parsing);
void		free_textures(t_params *params);
void		load_texture_color(float c[3], t_generic_object *intersected,
				t_point intersection);
void		load_checkerboard_color(float c[3], t_checkerboard board,
				t_generic_object *obj, t_point intersection);

#endif
