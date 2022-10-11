/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:57:09 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/11 13:18:39 by dhubleur         ###   ########.fr       */
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

#endif
