/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:05:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 14:13:29 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "render.h"

void	resize(int keycode, t_params *params)
{
	double	*size;

	if (params->selected == NULL)
		return ;
	if (params->selected->type == SPHERE)
		size = &(((t_sphere *)params->selected->specific_object)->diameter);
	else if (params->selected->type == CYLINDER)
	{
		if (keycode == XK_f || keycode == XK_g)
			size = &(((t_cylinder *)
						params->selected->specific_object)->diameter);
		else
			size = &(((t_cylinder *)params->selected->specific_object)->height);
	}
	else
		return ;
	if (keycode == XK_f || keycode == XK_e)
		*size -= 0.1;
	else
		*size += 0.1;
	if (*size < 0)
		*size = 0;
}
