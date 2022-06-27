/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/06/27 13:40:25 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
    double		x;
    double		y;
    double		z;
}   t_vector;

void normalize(t_vector *vector);
void vector_add(t_vector *vector, t_vector vector_add);
void vector_substract(t_vector *vector, t_vector vector_substract);
void multiply_by_scalar(t_vector *vector, double scalar);
void divide_by_scalar(t_vector *vector, double scalar);

#endif