/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/30 12:04:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parsing.h"
#include "render.h"
#include "window_props.h"
#include "events.h"

bool	is_parsing_complete(t_parsing *parsing)
{
	if (parsing->camera == NULL)
	{
		ft_putendl_fd("Error\nPlease specify a camera", 2);
		return (false);
	}
	if (parsing->ambient_lightning == NULL)
	{
		ft_putendl_fd("Error\nPlease specify an ambient lightning", 2);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_mlx		mlx;
	t_params	params;

	parsing.camera = NULL;
	parsing.ambient_lightning = NULL;
	parsing.lights = NULL;
	parsing.hittables = NULL;
	if (!parse_map(argc, argv, &parsing) || !is_parsing_complete(&parsing))
		return (free_parse(&parsing), 1);
	params.parsing = &parsing;
	if (init_mlx(&mlx) == false)
		return (free_parse(&parsing), 1);
	params.mlx = &mlx;
	params.selected = NULL;
	load_textures(params.mlx, params.parsing);
	init_events(&params);
	render_image(&params);
	mlx_loop(params.mlx->mlx);
	free_textures(&params);
	free_parse(&parsing);
	mlx_destroy_window(params.mlx->mlx, params.mlx->win);
	mlx_destroy_display(params.mlx->mlx);
	free(params.mlx->mlx);
	return (0);
}
