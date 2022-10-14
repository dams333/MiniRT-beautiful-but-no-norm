/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:09:47 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/14 13:17:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structures.h"

t_texture_infos	*extract_texture_infos(t_generic_object *obj)
{
	if (obj->type == SPHERE)
		return (&(((t_sphere *)obj->specific_object)->texture_infos));
	else if (obj->type == PLANE)
		return (&(((t_plane *)obj->specific_object)->texture_infos));
	else if (obj->type == CYLINDER)
		return (&(((t_cylinder *)obj->specific_object)->texture_infos));
	else
		return (&(((t_ellipsoid *)obj->specific_object)->texture_infos));
}
