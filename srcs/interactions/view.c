/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:05:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 14:21:01 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "render.h"

void	view(int keycode, t_params *params)
{
	if (keycode == XK_z)
		params->parsing->camera->horizontal_fov += 1;
	else if (keycode == XK_x)
		params->parsing->camera->horizontal_fov -= 1;
	if (params->parsing->camera->horizontal_fov < 0)
		params->parsing->camera->horizontal_fov = 0;
	if (params->parsing->camera->horizontal_fov > 180)
		params->parsing->camera->horizontal_fov = 180;
}
