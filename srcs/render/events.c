/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/01 15:22:26 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static int	on_key_press(int keycode, void *param)
{
	t_params	*params;

	params = (t_params *) param;
	if (keycode == XK_Escape)
		mlx_loop_end(params->mlx->mlx);
	else if (keycode != 65293)
	{
		key_pressed(keycode, params);
		render_image(params);
	}
	return (0);
}

static int	on_close_window(void *param)
{
	t_xvar	*xvar;

	xvar = (t_xvar *) param;
	mlx_loop_end(xvar);
	return (0);
}

static int	on_mouse_press(int code, int x, int y, void *param)
{
	t_params	*params;

	params = (t_params *)param;
	if (code == 1)
		click_on_screen(x, y, params);
	return (0);
}

void	init_events(t_params *params)
{
	mlx_hook(params->mlx->win, 33, 1L << 17,
		&on_close_window, params->mlx->mlx);
	mlx_key_hook(params->mlx->win, &on_key_press, params);
	mlx_mouse_hook(params->mlx->win, &on_mouse_press, params);
}
