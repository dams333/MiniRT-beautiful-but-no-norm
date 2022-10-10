/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:47:57 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 16:56:08 by dhubleur         ###   ########.fr       */
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
	mlx->data = NULL;
	mlx->img = NULL;
	return (true);
}

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	register_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	useless;

	if (!mlx->img || !mlx->data)
	{
		mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		mlx->data = (int *)mlx_get_data_addr(mlx->img,
				&useless, &useless, &useless);
	}
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	mlx->data[y * WINDOW_WIDTH + x] = color;
}

void	put_image(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	mlx->data = NULL;
}
