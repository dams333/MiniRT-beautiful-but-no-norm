/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:04:32 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/04 13:22:51 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERSECTION_H
# define OBJ_INTERSECTION_H

# include "structures.h"

typedef struct s_obj_intersection
{
	t_generic_object	*intersected;
	t_point				intersection;
}	t_obj_intersection;

#endif
