/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_degree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:51:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/17 14:55:22 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "sec_degree_utils.h"
#include <math.h>

double	calc_delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	get_first_root(double a, double b, double c)
{
	double	delta;

	delta = calc_delta(a, b, c);
	return ((-b - sqrt(delta)) / (2 * a));
}

double	get_second_root(double a, double b, double c)
{
	double	delta;

	delta = calc_delta(a, b, c);
	return ((-b + sqrt(delta)) / (2 * a));
}
