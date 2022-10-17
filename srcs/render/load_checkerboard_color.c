/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_checkerboard_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:18:24 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 16:00:16 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkerboard.h"
#include "render.h"

void	load_checkerboard_color(float c[3], t_checkerboard board,
			t_generic_object_metaed obj, t_point intersection)
{
	if (is_3d_filled(board, obj.obj, intersection, obj.is_cap))
	{
		c[0] = (float) board.color_r / 255;
		c[1] = (float) board.color_g / 255;
		c[2] = (float) board.color_b / 255;
	}
}
