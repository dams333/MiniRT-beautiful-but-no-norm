/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sp_filled.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:07:44 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/11 12:10:17 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkerboard.h"

int	is_sp_filled(t_checkerboard checkerboard, t_point point)
{
	t_point2d	board_pos;

	board_pos = to_checkerboard_pos(point);
	return (is_filled(checkerboard, board_pos.x, board_pos.y));
}
