/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:27 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/06 15:31:58 by dhubleur         ###   ########.fr       */
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

void	render_image(t_params *params);

#endif