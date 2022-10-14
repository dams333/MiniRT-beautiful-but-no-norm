/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_filled.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:32:05 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/14 15:41:38 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkerboard.h"

int	is_filled(t_checkerboard checkerboard, t_point2d board_pos)
{
	int	check_x;
	int	check_y;

	if (board_pos.x < 0)
		board_pos.x -= 1.0 / checkerboard.width;
	if (board_pos.y < 0)
		board_pos.y -= 1.0 / checkerboard.height;
	check_x = board_pos.x * checkerboard.width;
	check_y = board_pos.y * checkerboard.height;
	return ((check_x + check_y) % 2);
}
