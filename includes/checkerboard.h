/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:16:28 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/11 17:49:24 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_H
# define CHECKERBOARD_H

# include "geometric.h"

typedef struct s_checkerboard
{
	int	height;
	int	width;
	int	color_r;
	int	color_g;
	int	color_b;
}	t_checkerboard;

int			is_filled(t_checkerboard checkerboard, double x, double y);
int			is_sp_filled(t_checkerboard checkerboard, t_point point,
				t_point center);
t_point2d	to_checkerboard_pos(t_point point);

#endif
