/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:04:26 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/29 18:06:49 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"

void	cross_product(t_vector *result, t_vector *v1, t_vector *v2)
{
	result->x = v1->y * v2->z - v1->z * v2->y;
	result->y = v1->z * v2->x - v1->x * v2->z;
	result->z = v1->x * v2->y - v1->y * v2->x;
}
