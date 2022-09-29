/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scalar_operation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:26 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/29 17:44:51 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"

void	multiply_by_scalar(t_vector *vec, double scalar)
{
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}

void	divide_by_scalar(t_vector *vec, double scalar)
{
	vec->x /= scalar;
	vec->y /= scalar;
	vec->z /= scalar;
}
