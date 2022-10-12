/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_filled.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:32:05 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/12 12:28:31 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkerboard.h"

int	is_filled(t_checkerboard checkerboard, t_point2d board_pos)
{
	int	check_x;
	int	check_y;

	check_x = board_pos.x * checkerboard.width;
	check_y = board_pos.y * checkerboard.height;
	return ((check_x + check_y) % 2);
}
