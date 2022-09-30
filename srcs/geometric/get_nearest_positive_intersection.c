/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nearest_positive_intersection.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:15:51 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/29 19:19:09 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "get_nearest_positive_intersection.h"
#include "sec_degree_utils.h"

double	get_nearest_positive_intersection(double a, double b, double c)
{
	double	first_root;
	double	second_root;

	first_root = get_first_root(a, b, c);
	second_root = get_second_root(a, b, c);
	if (isnan(first_root) || (first_root < 0 && second_root < 0))
		return (NAN);
	if (first_root > 0 && first_root < second_root)
		return (first_root);
	else
		return (second_root);
}
