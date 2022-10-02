/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_degree_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:48:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/02 11:23:34 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEC_DEGREE_UTILS_H
# define SEC_DEGREE_UTILS_H

# include "geometric.h"

double	calc_delta(double a, double b, double c);
double	get_first_root(double a, double b, double c);
double	get_second_root(double a, double b, double c);
double	calc_distance_from_ray_and_time(t_ray ray, double t);

#endif
