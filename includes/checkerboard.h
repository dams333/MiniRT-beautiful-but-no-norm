/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:16:28 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/17 15:36:45 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_H
# define CHECKERBOARD_H

# include "geometric.h"
# include "structures.h"

int			is_filled(t_checkerboard checkerboard, t_point2d board_pos);
int			is_3d_filled(t_checkerboard board, t_generic_object *obj,
				t_point intersection, int is_cap);
t_point2d	to_checkerboard_pos(t_generic_object *obj, t_point intersection,
				int is_cap);

#endif
