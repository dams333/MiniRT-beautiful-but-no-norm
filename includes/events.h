/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:57:09 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/11 14:22:56 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "mlx.h"
# include "mlx_int.h"
# include <X11/keysymdef.h> 
# include <stdlib.h>
# include <stdbool.h>
# include "render.h"

void	init_events(t_params *params);
void	click_on_screen(int x, int y, t_params *params);
void	key_pressed(int keycode, t_params *params);
void	move(int keycode, t_params *params);
void	resize(int keycode, t_params *params);
void	view(int keycode, t_params *params);
void	rotate(int keycode, t_params *params);

#endif
