/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_3d_filled.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:47 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/12 12:28:59 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkerboard.h"

int	is_3d_filled(t_checkerboard board, t_generic_object *obj,
		t_point intersection)
{
	t_point2d	board_pos;

	board_pos = to_checkerboard_pos(obj, intersection);
	return (is_filled(board, board_pos));
}
