/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/07/19 15:23:21 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysymdef.h>

#include "mlx.h"
#include "mlx_int.h"

static int	on_key_press(int keycode, void *param);

void	init_events(t_xvar *xvar, t_win_list *win)
{
	mlx_key_hook(win, &on_key_press, xvar);
}

static int	on_key_press(int keycode, void *param)
{
	t_xvar	*xvar;

	xvar = (t_xvar *) param;
	if (keycode == XK_Escape)
		mlx_loop_end(xvar);
	return (0);
}
