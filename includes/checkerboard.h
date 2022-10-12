/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:16:28 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/12 12:29:20 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_H
# define CHECKERBOARD_H

# include "geometric.h"
# include "structures.h"

typedef struct s_checkerboard
{
	int	height;
	int	width;
	int	color_r;
	int	color_g;
	int	color_b;
}	t_checkerboard;

int			is_filled(t_checkerboard checkerboard, t_point2d board_pos);
int			is_3d_filled(t_checkerboard board, t_generic_object *obj,
				t_point intersection);
t_point2d	to_checkerboard_pos(t_generic_object *obj, t_point intersection);

#endif
