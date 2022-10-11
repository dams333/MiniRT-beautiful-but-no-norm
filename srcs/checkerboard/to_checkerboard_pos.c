/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_checkerboard_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:57:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/11 12:10:35 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "checkerboard.h"

t_point2d	to_checkerboard_pos(t_point point)
{
	t_spherical_point	sp_point;
	t_point2d			board_point;

	sp_point = to_spherical(point);
	board_point.x = sp_point.azimuth / (2 * M_PI);
	board_point.y = sp_point.inclination / M_PI;
	return (board_point);
}
