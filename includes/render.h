/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:27 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 13:31:26 by dhubleur         ###   ########.fr       */
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
	t_parsing	*parsing;
	t_mlx		*mlx;
}	t_params;

void		render_image(t_params *params);
void		compute_pixel(t_params *params, t_obj_intersection intersection,
				int canvas_x, int canvas_y);
void		get_obj_color(float color[3], t_generic_object *intersected);
t_vector	compute_normal(t_obj_intersection intersection);
void		compute_diffuse_lightning(t_obj_intersection intersection,
				t_vector normal, t_light_object *light,
				float obj[3], float res[3]);

#endif