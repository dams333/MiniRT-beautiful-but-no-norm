/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_props.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:48:26 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/11 13:16:46 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_PROPS_H
# define WINDOW_PROPS_H

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_NAME "MiniRT"

# include "mlx.h"
# include "mlx_int.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
}	t_mlx;

bool	init_mlx(t_mlx *mlx);

#endif
