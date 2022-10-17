/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:59:34 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/15 17:32:33 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATE_H
# define ROTATE_H

# include "geometric.h"

void	rotate_around_x(t_vector *vec, double angle);
void	rotate_around_y(t_vector *vec, double angle);
void	rotate_around_z(t_vector *vec, double angle);

#endif
