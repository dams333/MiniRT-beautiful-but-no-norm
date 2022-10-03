/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_props.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:48:26 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/27 17:52:53 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_PROPS_H
# define WINDOW_PROPS_H

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_NAME "MiniRT"

# include "mlx.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

bool	init_mlx(t_mlx *mlx);

#endif
