/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotation_angles.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:27:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/15 17:48:05 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ROTATION_ANGLES_H
# define GET_ROTATION_ANGLES_H

# include "geometric.h"

double	get_rotation_angle(t_vector from, t_vector to);
double	get_x_rotation_angle(t_vector from, t_vector to);
double	get_y_rotation_angle(t_vector from, t_vector to);
double	get_z_rotation_angle(t_vector from, t_vector to);

#endif
