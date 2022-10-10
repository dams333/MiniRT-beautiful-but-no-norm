/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:04:32 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/10 14:05:54 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERSECTION_H
# define OBJ_INTERSECTION_H

# include "structures.h"
# include "geometric.h"

typedef struct s_obj_intersection
{
	t_generic_object	*intersected;
	t_point				intersection;
	t_vector			normal;
}	t_obj_intersection;

#endif
