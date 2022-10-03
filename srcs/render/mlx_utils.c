/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:47:57 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/27 17:48:04 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "window_props.h"
#include "libft.h"

bool	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (!mlx->win)
		return (false);
	return (true);
}
